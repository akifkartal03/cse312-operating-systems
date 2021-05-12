/* SPIM S20 MIPS simulator.
   Execute SPIM syscalls, both in simulator and bare mode.
   Execute MIPS syscalls in bare mode, when running on MIPS systems.
   Copyright (c) 1990-2010, James R. Larus.
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

   Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

   Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation and/or
   other materials provided with the distribution.

   Neither the name of the James R. Larus nor the names of its contributors may be
   used to endorse or promote products derived from this software without specific
   prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
   GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef _WIN32
#include <unistd.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>

#ifdef _WIN32
#include <io.h>
#endif

#include "spim.h"
#include "string-stream.h"
#include "inst.h"
#include "reg.h"
#include "mem.h"
#include "sym-tbl.h"
#include "syscall.h"
#include "spim-utils.h"
#define BYTES_TO_INST(N) (((N) + BYTES_PER_WORD - 1) / BYTES_PER_WORD * sizeof(instruction *))

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#ifdef _WIN32
/* Windows has an handler that is invoked when an invalid argument is passed to a system
   call. https://msdn.microsoft.com/en-us/library/a9yf33zb(v=vs.110).aspx

   All good, except that the handler tries to invoke Watson and then kill spim with an exception.

   Override the handler to just report an error.
*/

#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

void myInvalidParameterHandler(const wchar_t* expression,
   const wchar_t* function, 
   const wchar_t* file, 
   unsigned int line, 
   uintptr_t pReserved)
{
  if (function != NULL)
    {
      run_error ("Bad parameter to system call: %s\n", function);
    }
  else
    {
      run_error ("Bad parameter to system call\n");
    }
}

static _invalid_parameter_handler oldHandler;

void windowsParameterHandlingControl(int flag )
{
  static _invalid_parameter_handler oldHandler;
  static _invalid_parameter_handler newHandler = myInvalidParameterHandler;

  if (flag == 0)
    {
      oldHandler = _set_invalid_parameter_handler(newHandler);
      _CrtSetReportMode(_CRT_ASSERT, 0); // Disable the message box for assertions.
    }
  else
    {
      newHandler = _set_invalid_parameter_handler(oldHandler);
      _CrtSetReportMode(_CRT_ASSERT, 1);  // Enable the message box for assertions.
    }
}
#endif

/*define thread properties*/
typedef struct Thread{
    /*thread specific info*/
    //program counter
    //register
    //stack
    //state
    int threadID;
    char name[41];
    char funcName[41];
    State currentState;
    mem_addr t_PC, t_nPC; // program counter
    reg_word t_R[R_LENGTH]; // registers.
    /*thread stack*/
    int t_stack_size;
    mem_word *t_stack_seg;
    short *t_stack_seg_h;
    BYTE_TYPE *t_stack_seg_b;
    mem_addr t_stack_bot;

}thread;
/*init process info*/
typedef struct InitProcess{
    /*Initial Process Info*/
    int processID;// will be 0

    //process specific data
    reg_word i_R[R_LENGTH];
    reg_word i_HI, i_LO;
    mem_addr i_PC, i_nPC;
    reg_word i_CCR[4][32], i_CPR[4][32];
    instruction **i_text_seg;
    bool i_text_modified;
    mem_addr i_text_top;
    mem_word *i_data_seg;
    bool i_data_modified;
    short *i_data_seg_h;
    BYTE_TYPE *i_data_seg_b;
    mem_addr i_data_top;
    mem_addr i_gi_midpoint;
    mem_word *i_stack_seg;
    short *i_stack_seg_h;
    BYTE_TYPE *i_stack_seg_b;
    mem_addr i_stack_bot;
    instruction **i_k_text_seg;
    mem_addr i_k_text_top;
    mem_word *i_k_data_seg;
    short *i_k_data_seg_h;
    BYTE_TYPE *i_k_data_seg_b;
    mem_addr i_k_data_top;
    int i_data_size;
    int i_stack_size;
    int i_k_data_size;

}initProcess;
class HandleThread{
public:
    HandleThread(){
        myThread.currentState=Blocked;
        myThread.threadID = -1;
    };
    HandleThread(thread newThread){
        myThread = newThread;
    }
    /*getters and setters*/
    int getThreadID() const {
        return myThread.threadID;
    }

    State getCurrentState() const {
        return myThread.currentState;
    }

    char* getName(){
        return myThread.name;
    }
    char* getFuncName(){
        return myThread.funcName;
    }
    void setID(int newID){
        myThread.threadID = newID;
    }
    void setName(char newName[41]){
        strcpy(myThread.name,newName);
    }
    void setFuncName(char newName[41]){
        strcpy(myThread.funcName,newName);
    }
    void setCurrentState(State state){
        myThread.currentState = state;
    }
    thread getThread(){
        return myThread;
    }
    void setThread(thread newThread){
        myThread = newThread;
    }
    void setThreadSpecificData(){
        myThread.t_stack_seg_h = stack_seg_h;
        myThread.t_stack_seg_b = stack_seg_b;
        myThread.t_stack_bot = stack_bot;
        myThread.t_stack_seg = stack_seg;
        myThread.t_nPC = nPC;
        myThread.t_PC = PC;
        memcpy(myThread.t_R, R, R_LENGTH * sizeof(reg_word));
    }
    void getThreadSpecificData(){
        stack_seg_h = myThread.t_stack_seg_h;
        stack_seg_b = myThread.t_stack_seg_b;
        stack_bot = myThread.t_stack_bot;
        stack_seg = myThread.t_stack_seg;
        nPC = myThread.t_nPC;
        PC = myThread.t_PC;
        memcpy(R, myThread.t_R, R_LENGTH * sizeof(reg_word));
    }

    void printThreadInfo(){
        write_output(console_out,"ThreadID:%d\nThread Name:%s\nThread Function Name:%s\nProgram Counter:0x%x\nStack Pointer address:%d\n",
                     myThread.threadID,myThread.name,myThread.funcName,myThread.t_PC,myThread.threadID);
        switch (myThread.currentState){
            case State::Blocked:
                write_output(console_out, "State:Blocked\n");
                break;
            case State::Running:
                write_output(console_out, "State:Running\n");
                break;
            case State::Ready:
                write_output(console_out, "State:Ready\n");
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }
    void giveResources(){
        free(myThread.t_stack_seg);
    }
    ~HandleThread(){
        giveResources();
    }
private:
    thread myThread;
};
class HandleInitProcess{
public:
    HandleInitProcess(){
        process.processID = 0;
        setProcess();
        tid = 1;
        //createThread(true);
        //doContextSwitch(1);

    }
    HandleInitProcess(InitProcess newProcess){
        process = newProcess;
    }
    int getInitProcessID() const {
        return process.processID;
    }
    void addNewThread(HandleThread *thread1){
        threadTable.push_back(thread1);
    }
    void setProcess(){
        process.i_data_size = ROUND_UP(initial_data_size, BYTES_PER_WORD);
        process.i_stack_size = ROUND_UP(initial_stack_size, BYTES_PER_WORD);
        process.i_k_data_size = ROUND_UP(initial_k_data_size, BYTES_PER_WORD);
        process.i_data_seg = (mem_word *) xmalloc( process.i_data_size);
        process.i_stack_seg = (mem_word *) xmalloc( process.i_stack_size);
        process.i_k_data_seg = (mem_word *) xmalloc( process.i_k_data_size);

        process.i_data_seg = data_seg;
        process.i_stack_seg = stack_seg;
        process.i_k_data_seg = k_data_seg;

        memcpy(process.i_R, R, R_LENGTH * sizeof(reg_word));
        process.i_HI = HI;
        process.i_LO = LO;
        process.i_PC = PC;
        process.i_nPC = nPC;
        memcpy(process.i_CCR, CCR, 128 * sizeof(reg_word));
        memcpy(process.i_CPR, CPR, 128 * sizeof(reg_word));
        process.i_text_modified = text_modified;
        process.i_text_top = text_top;
        process.i_data_modified = data_modified;
        process.i_data_seg_h = data_seg_h;
        process.i_data_seg_b = data_seg_b;
        process.i_data_top = data_top;
        process.i_gi_midpoint = gp_midpoint;
        process.i_stack_seg_h = stack_seg_h;
        process.i_stack_seg_b = stack_seg_b;
        process.i_stack_bot = stack_bot;
        process.i_k_text_seg = k_text_seg;
        process.i_k_text_top = k_text_top;
        process.i_k_data_seg_h = k_data_seg_h;
        process.i_k_data_seg_b = k_data_seg_b;
        process.i_k_data_top = k_data_top;
        process.i_k_data_seg_b = (BYTE_TYPE *) k_data_seg;
        process.i_k_data_seg_h = (short *) k_data_seg;
        //memcpy(process.i_data_seg, data_seg, process.i_data_size);
        //memcpy(process.i_stack_seg, stack_seg, process.i_stack_size);
        //memcpy(process.i_k_data_seg, k_data_seg, process.i_k_data_size);
        process.i_text_seg = text_seg;
        process.i_k_text_seg = k_text_seg;
    }
    void getProcess(){
        text_seg = process.i_text_seg;
        k_text_seg = process.i_k_text_seg;
        data_seg = process.i_data_seg;
        stack_seg = process.i_stack_seg;
        k_data_seg = process.i_k_data_seg;

        memcpy(R, process.i_R, R_LENGTH * sizeof(reg_word));
        HI = process.i_HI;
        LO = process.i_LO;
        PC = process.i_PC;
        nPC = process.i_nPC;
        memcpy(CCR, process.i_CCR, 128 * sizeof(reg_word));
        memcpy(CPR, process.i_CPR, 128 * sizeof(reg_word));
        text_modified = process.i_text_modified;
        text_top = process.i_text_top;
        data_modified = process.i_data_modified;
        data_seg_h = process.i_data_seg_h;
        data_seg_b = process.i_data_seg_b;
        data_top = process.i_data_top;
        gp_midpoint = process.i_gi_midpoint;
        stack_seg_h = process.i_stack_seg_h;
        stack_seg_b = process.i_stack_seg_b;
        stack_bot = process.i_stack_bot;
        k_text_seg = process.i_k_text_seg;
        k_text_top = process.i_k_text_top;
        k_data_seg_h = process.i_k_data_seg_h;
        k_data_seg_b = process.i_k_data_seg_b;
        k_data_top = process.i_k_data_top;
        k_data_seg_b = (BYTE_TYPE *) process.i_k_data_seg;
        k_data_seg_h = (short *) process.i_k_data_seg;
    }
    void createThread(bool isMain){
        auto *thread3 = new HandleThread();
        thread3->setID(tid);
        char tempName[41];
        if (isMain)
            sprintf(tempName,"main");
        else
            sprintf(tempName,"thread%d",tid);
        thread3->setName(tempName);
        thread3->setCurrentState(Ready);
        PC += BYTES_PER_WORD;
        thread3->setThreadSpecificData();
        PC -= BYTES_PER_WORD;
        if (isMain) {
            thread3->setFuncName("main");
        }
        else{
            char filename[41];
            strcpy(filename, (char*) mem_reference (R[REG_A0]));
            thread3->setFuncName(filename);
        }
        threadTable.push_back(thread3);
        readyQueue.push(thread3->getThreadID());
        tid++;
        printAllThreads();
        R[REG_V0] = 0;
    }
    //join is waiting a any thread
    void joinThread(){
        int result = -2;
        int id = getWaiting();
        if (id != curTid){
            if (id != -1){
                if (isFinished(id)){
                    result = id;
                    removeThread(id);
                }
                else{
                    result = 0;
                }
            }
            else{
                result = -1; //no child is waiting
            }
        }
        else{
            if (threadTable.size() > 1){
                result  = 0;
            }
            else{
                result = -1;
            }
        }
        R[REG_V0] = result;
        doContextSwitch(1);

    }
    int getWaiting(){
        if (threadTable.empty())
            return -1;
        else{
            threadTable.front()->getThreadID();
        }
    }
    void doContextSwitch(int finished){
        if (readyQueue.empty())
            return;
        HandleThread *next = getThread(readyQueue.front());
        readyQueue.pop();
        if (!finished)
            handleInterrupt();
        next->setCurrentState(Running);
        curTid = next->getThreadID();
        next->setThreadSpecificData();
        write_output(console_out, "****Thread is Changing*****\n");
        next->printThreadInfo();
        if (next->getThreadID() != 0){
            runAsm(next->getFuncName());
        }
    }
    void handleInterrupt(){
        HandleThread *curr = getThread(curTid);
        curr->setCurrentState(Blocked);
        curr->getThreadSpecificData();
        readyQueue.push(curTid);
    }
    void printAllThreads(){
        for (auto & thr : threadTable) {
            thr->printThreadInfo();
        }
    }
    bool isFinished(int threadID){
        for (auto & thr : threadTable) {
            if(thr->getThreadID() == threadID)
                return false;
        }
        return true;
    }
    int getCurrent(){
        for (auto & thr : threadTable) {
            if(thr->getCurrentState() == Running)
                return thr->getThreadID();
        }
        return -1;
    }
    HandleThread *getThread(int id){
        for (auto & thr : threadTable) {
            if(thr->getThreadID() == id)
                return thr;
        }
    }
    void removeThread(int id){
        int i = 0;
        int index = -1;
        for (auto & thr : threadTable) {
            if(thr->getThreadID() == id){
                index = i;
            }
            i++;
        }
        if (index != -1){
            threadTable.erase(threadTable.begin() + index);
        }
    }
    void exitThread(int id){
        removeThread(id);
    }
    void runAsm(char *filename){
        if (access(filename, F_OK) != -1) {

            thread temp = getThread(curTid)->getThread();
            write_output(console_out, "FİLEName::%s\n",filename);
            temp.t_stack_seg = NULL;
            write_output(console_out, "heree1\n");
            getThread(curTid)->setThread(temp);
            getProcess();
            text_seg = NULL;
            data_seg = NULL;
            k_text_seg = NULL;
            k_data_seg = NULL;

            initialize_world(exception_file_name, false);
            read_assembly_file(filename);
            write_output(console_out, "heree2\n");
            thread temp2 = getThread(curTid)->getThread();
            PC = starting_address();
            setProcess();
            temp2.t_PC = starting_address();
            getThread(curTid)->setThread(temp2);
            write_output(console_out, "heree3\n");
        }
        else
        {
            write_output(console_out, "%s is not found!!", filename);
        }
    }
    void clearAll(){
        for (auto & thr : threadTable) {
            thr->giveResources();
        }
        free(process.i_data_seg);
        free(process.i_stack_seg);
        free(process.i_k_data_seg);
    }
    int getTID(){
        return tid;
    }
    int getCurrTid(){
        return curTid;
    }
    void createInit(){
        process.processID = 0;
        setProcess();
    }
    bool isEmpty(){
        return (threadTable.size() == 0);
    }
private:
    InitProcess process;
    vector<HandleThread*> threadTable;
    queue<int> readyQueue; //round robing scheduling thread queue.
    int tid; //counter for unique tid
    int curTid;
};

HandleInitProcess kernel;
/*You implement your handler here*/
void SPIM_timerHandler()
{
    // Implement your handler..
    kernel.doContextSwitch(0);

}


/* Decides which syscall to execute or simulate.  Returns zero upon
   exit syscall and non-zero to continue execution. */
int
do_syscall ()
{
#ifdef _WIN32
    windowsParameterHandlingControl(0);
#endif

  /* Syscalls for the source-language version of SPIM.  These are easier to
     use than the real syscall and are portable to non-MIPS operating
     systems. */

  switch (R[REG_V0])
    {
    case PRINT_INT_SYSCALL:
      write_output (console_out, "%d", R[REG_A0]);
      break;

    case PRINT_FLOAT_SYSCALL:
      {
	float val = FPR_S (REG_FA0);

	write_output (console_out, "%.8f", val);
	break;
      }

    case PRINT_DOUBLE_SYSCALL:
      write_output (console_out, "%.18g", FPR[REG_FA0 / 2]);
      break;

    case PRINT_STRING_SYSCALL:
      write_output (console_out, "%s", mem_reference (R[REG_A0]));
      break;

    case READ_INT_SYSCALL:
      {
	static char str [256];

	read_input (str, 256);
	R[REG_RES] = atol (str);
	break;
      }

    case READ_FLOAT_SYSCALL:
      {
	static char str [256];

	read_input (str, 256);
	FPR_S (REG_FRES) = (float) atof (str);
	break;
      }

    case READ_DOUBLE_SYSCALL:
      {
	static char str [256];

	read_input (str, 256);
	FPR [REG_FRES] = atof (str);
	break;
      }

    case READ_STRING_SYSCALL:
      {
	read_input ( (char *) mem_reference (R[REG_A0]), R[REG_A1]);
	data_modified = true;
	break;
      }

    case SBRK_SYSCALL:
      {
	mem_addr x = data_top;
	expand_data (R[REG_A0]);
	R[REG_RES] = x;
	data_modified = true;
	break;
      }

    case PRINT_CHARACTER_SYSCALL:
      write_output (console_out, "%c", R[REG_A0]);
      break;

    case READ_CHARACTER_SYSCALL:
      {
	static char str [2];

	read_input (str, 2);
	if (*str == '\0') *str = '\n';      /* makes xspim = spim */
	R[REG_RES] = (long) str[0];
	break;
      }

    case EXIT_SYSCALL:
      spim_return_value = 0;
      return (0);

    case EXIT2_SYSCALL:
      spim_return_value = R[REG_A0];	/* value passed to spim's exit() call */
      return (0);

    case OPEN_SYSCALL:
      {
#ifdef _WIN32
        R[REG_RES] = _open((char*)mem_reference (R[REG_A0]), R[REG_A1], R[REG_A2]);
#else
	R[REG_RES] = open((char*)mem_reference (R[REG_A0]), R[REG_A1], R[REG_A2]);
#endif
	break;
      }

    case READ_SYSCALL:
      {
	/* Test if address is valid */
	(void)mem_reference (R[REG_A1] + R[REG_A2] - 1);
#ifdef _WIN32
	R[REG_RES] = _read(R[REG_A0], mem_reference (R[REG_A1]), R[REG_A2]);
#else
	R[REG_RES] = read(R[REG_A0], mem_reference (R[REG_A1]), R[REG_A2]);
#endif
	data_modified = true;
	break;
      }

    case WRITE_SYSCALL:
      {
	/* Test if address is valid */
	(void)mem_reference (R[REG_A1] + R[REG_A2] - 1);
#ifdef _WIN32
	R[REG_RES] = _write(R[REG_A0], mem_reference (R[REG_A1]), R[REG_A2]);
#else
	R[REG_RES] = write(R[REG_A0], mem_reference (R[REG_A1]), R[REG_A2]);
#endif
	break;
      }

    case CLOSE_SYSCALL:
      {
#ifdef _WIN32
	R[REG_RES] = _close(R[REG_A0]);
#else
	R[REG_RES] = close(R[REG_A0]);
#endif
	break;
      }
        case CREATE_THREAD_SYSCALL: {
            write_output(console_out, "neler oluyor burdaaaaaa!!!\n");
            kernel.createThread(false);
            //kernel.doContextSwitch(0);
            break;
        }

        case JOIN_THREAD_SYSCALL: {
            kernel.joinThread();
            break;
        }


        case EXIT_THREAD_SYSCALL: {
            spim_return_value = 0;

            if (kernel.isEmpty()) // if no thread then terminate
                return 0;
            else // delete current thread.
                kernel.removeThread(kernel.getCurrent());
            kernel.doContextSwitch(1);
            PC -=4;
            break;
        }


        case LOCK_MUTEX_SYSCALL:{

            break;
        }
        case UNLOCK_MUTEX_SYSCALL:{

            break;
        }
        case LOAD_ASM_SYSCALL:{
            kernel.doContextSwitch(0);
            break;
        }


        default:
      run_error ("Unknown system call: %d\n", R[REG_V0]);
      break;
    }

#ifdef _WIN32
    windowsParameterHandlingControl(1);
#endif
  return (1);
}


void
handle_exception ()
{
  if (!quiet && CP0_ExCode != ExcCode_Int)
    error ("Exception occurred at PC=0x%08x\n", CP0_EPC);

  exception_occurred = 0;
  PC = EXCEPTION_ADDR;

  switch (CP0_ExCode)
    {
    case ExcCode_Int:
      break;

    case ExcCode_AdEL:
      if (!quiet)
	error ("  Unaligned address in inst/data fetch: 0x%08x\n", CP0_BadVAddr);
      break;

    case ExcCode_AdES:
      if (!quiet)
	error ("  Unaligned address in store: 0x%08x\n", CP0_BadVAddr);
      break;

    case ExcCode_IBE:
      if (!quiet)
	error ("  Bad address in text read: 0x%08x\n", CP0_BadVAddr);
      break;

    case ExcCode_DBE:
      if (!quiet)
	error ("  Bad address in data/stack read: 0x%08x\n", CP0_BadVAddr);
      break;

    case ExcCode_Sys:
      if (!quiet)
	error ("  Error in syscall\n");
      break;

    case ExcCode_Bp:
      exception_occurred = 0;
      return;

    case ExcCode_RI:
      if (!quiet)
	error ("  Reserved instruction execution\n");
      break;

    case ExcCode_CpU:
      if (!quiet)
	error ("  Coprocessor unuable\n");
      break;

    case ExcCode_Ov:
      if (!quiet)
	error ("  Arithmetic overflow\n");
      break;

    case ExcCode_Tr:
      if (!quiet)
	error ("  Trap\n");
      break;

    case ExcCode_FPE:
      if (!quiet)
	error ("  Floating point\n");
      break;

    default:
      if (!quiet)
	error ("Unknown exception: %d\n", CP0_ExCode);
      break;
    }
}
