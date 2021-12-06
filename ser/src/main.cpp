#include <avr/pgmspace.h>
#include <util/delay.h>
#include <util/atomic.h>

#include "usart.h"
#include "reset_status.h"
#include "timer_counter.h"
#include "port.h"
#include "loggger.h"
#include "format.h"

//
//namespace savr {
//    namespace timer_counter_0_A {
//        enum class WaveformGenerationMode {
//            // increment, 0x00 - 0xFF[signal and clear counter]
//            normal,
//            // increment, 0x00 - [signal and clear counter]
//            compare_match,
//            // increment, 0x00 - [signal] - 0xFF [clear counter]
//            fast_pwm,
//            // increment and decrement 0x00 - [signal] - 0xFF - [signal] - 0x00
//            phase_correction_pwm,
//
//        };
//
//        namespace control {
//            volatile uint8_t a IO(TCCR0A, 0x24);
//            volatile uint8_t b IO(TCCR0B, 0x25);
//
//            const uint8_t clock_mask = (1 << CS02) | (1 << CS01) | (1 << CS00);
//            const uint8_t io_clock = (1 << CS00);
//            const uint8_t io_clock_8 = (1 << CS01);
//            const uint8_t io_clock_64 = (1 << CS01) | (1 << CS00);
//            const uint8_t io_clock_256 = (1 << CS02);
//            const uint8_t io_clock_1024 = (1 << CS02) | (1 << CS00);
//            const uint8_t external_clock_falling_edge = (1 << CS02) | (1 << CS01);
//            const uint8_t external_clock_rising_edge = (1 << CS02) | (1 << CS01) | (1 << CS00);
//        }
//
//        volatile uint8_t counter IO(TCNT0, 0x26);
//        volatile uint8_t compare_a IO(OCR0A, 0x27);
//        volatile uint8_t compare_b IO(OCR0B, 0x28);
//
//
//        namespace interrupt_mask {
//            const uint8_t match_b = 1 << OCIE0B;
//            const uint8_t match_a = 1 << OCIE0A;
//            const uint8_t overflow = 1 << TOIE0;
//
//            volatile uint8_t value MEM(TIMSK0, 0x6E);
//        }
//
//        namespace interrupt_flags {
//            const uint8_t match_b = 1 << OCF0B;
//            const uint8_t match_a = 1 << OCF0A;
//            const uint8_t overflow = 1 << TOV0;
//
//            volatile uint8_t value IO(TIFR0, 0x15);
//        }
//
//
//
//        volatile uint8_t v __attribute__((io(0x24 + __SFR_OFFSET)));
//
//        template<class Mode>
//        class TC {
//
//        };
//    }
//}
//
//void test()
//{
//
//}



// usart test
//int main() {
//    using namespace savr::usart;
//    Usart<savr::usart::AsyncClock<9600, true>> uart(false);
//    uart.sync_send('A');
//    uart.sync_send(S("AB-AB"));
//    uart.sync_send(P("BA-BA"));

//    uart.sync_send('B');
//    uart.sync_send(S("BB-BB"));
//    uart.sync_send(P("BC-BC"));
//
//    uart.sync_send('C');
//}

// usart test + fmt
//volatile int8_t i_8 MEM(0, 0x800);
//volatile uint8_t u_8 MEM(0, 0x800);
//volatile int16_t i_16 MEM(0, 0x800);
//volatile uint16_t u_16 MEM(0, 0x800);
//
//int main() {
//    using namespace savr::usart;
//    using namespace savr::format;
//    Usart<savr::usart::AsyncClock<9600, true>> uart(false);
//    uart.sync_send(Fmt<int8_t>::format(0xA0));
//    uart.sync_send(Fmt<uint8_t>::format(0xA0));
//    uart.sync_send(Fmt<int16_t>::format(0xA0));
//    uart.sync_send(Fmt<uint16_t>::format(0xA0));
//
//    uart.sync_send(Fmt<int8_t>::format(i_8));
//    uart.sync_send(Fmt<uint8_t>::format(u_8));
//    uart.sync_send(Fmt<int16_t>::format(i_16));
//    uart.sync_send(Fmt<uint16_t>::format(u_16));
//
//    uart.sync_send(Fmt<bool>::format(u_8 == 0xF0));
//}


// logger test
//savr::logging::SyncLogger<
//        savr::logging::Level::Debug,
//        savr::usart::Usart<savr::usart::AsyncClock<9600, true>>
//> logger;
//volatile uint8_t u_8 MEM(0, 0x800);
//volatile uint8_t u_88 MEM(0, 0x400);
//int main() {
//
//    ERROR("Error msg");
//    INFO("Info message");
//    DEBUG("Details");
//
//    uint8_t t = u_8;
//    ERROR("Details with", t);
//    DEBUG("Details with", t);
//    uint8_t tt = u_88;
//    INFO("Info to", tt);
//
//    {
//        ERROR("A");
//        INFO("B");
//        DEBUG("C");
//
//        uint8_t tl = u_8;
//        ERROR("D", tl);
//        DEBUG("E", tl);
//        uint8_t ttl = u_88;
//        INFO("F", ttl);
//    }
//}

// reset status
//int main() {
//    using namespace savr;
//    cli();
//    watch_dog.reset();
//    watch_dog |= WatchDog::change_enabled | WatchDog::system_reset_enabled;
//    watch_dog = WatchDog::prescalar_64k;
//    sei();
//
//    usart::Usart<savr::usart::AsyncClock<9600, true>> uart;
//    uart.sync_send(P("Start"));
//    while(true) {}
//    return 0;
//}

savr::logging::SyncLogger<savr::logging::Level::Debug, savr::usart::Usart<savr::usart::AsyncClock<>>> logger;
//
//int main() {
//    INFO("Start");
//    using namespace savr;
//
//    if (mcu_status.is_set(McuStatus::power_on_reset)) {
//        INFO("Power on");
//    }
//    if (mcu_status.is_set(McuStatus::external_reset)) {
//        INFO("External reset");
//    }
//    if (mcu_status.is_set(McuStatus::watch_dog_system_reset)) {
//        INFO("Watch dog reset");
//    }
//    if (mcu_status.is_set(McuStatus::brown_out_reset)) {
//        INFO("Brown out reset");
//    }
//    mcu_status.clear();
//
//    using namespace timer_0;
//
//    timer_0::regs::output_compare_a = 0xFF;
//    timer_0::regs::output_compare_b = timer_0::regs::output_compare_a / 2;
//    control_b = ControlB::source_prescaler_1024;
//    control_a = ControlA::mode_clear_on_match | ControlA::output_a_set_on_match | ControlA::output_b_clear_on_match;
//    timer_0::output_a.init();
//    timer_0::output_b.init();
//
//    while(true) {
//        timer_0::regs::output_compare_a--;
//        timer_0::regs::output_compare_b = timer_0::regs::output_compare_a / 2;
//        uint8_t counter = timer_0::regs::counter;
//        INFO("Current timer: ", counter);
//    }
//}
//
//
//template<uint8_t size>
//class ThreadStack {
//    uint8_t stack[size];
//
//};
//
//class Lock {
//public:
//
//};
//
//class Task {
//public:
//    static
//    void run() {
//        asm volatile ("TASK1");
//    }
//
//    static constexpr
//    uint8_t thread_mask() {
//        return 0x01u;
//    }
//};
//
//class Task2 {
//public:
//    static
//    void run() {
//        asm volatile ("TASK2");
//
//    }
//
//    static constexpr
//    uint8_t thread_mask() {
//        constexpr uint8_t previous_mask = Task::thread_mask();
//        static_assert(previous_mask != 0x80u, "Attempt to create 9th task");
//        return previous_mask << 1;
//    }
//};
//
//
//volatile uint8_t BaseScheduler::_ready_mask = 0x0;
////
////class Mutex {
////    volatile uint8_t _mask;
////
////public:
////    void lock() {
////
////    }
////
////    void try_lock() {
////    }
////
////    void unlock() {
////
////    }
////};
//
//template<class PreviousTask>
//class NTask {
//
//private:
//
//
//    class Mutex {
//    private:
//        volatile uint8_t _mask;
//    public:
//        void lock() {
//            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
//                const auto current_mask = NTask::thread_mask();
//                _mask |= current_mask;
//                BaseScheduler::block_and_reschedule(current_mask);
//            }
//        }
//
//        bool try_lock() {
//            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
//                const auto mask = _mask;
//                const auto current_mask = NTask::thread_mask();
//                if(mask != 0x0) {
//                    return false;
//                }
//                _mask = mask | current_mask;
//                BaseScheduler::block_and_reschedule(current_mask);
//            }
//        }
//
//        void unlock() {
//            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
//                BaseScheduler::unblock_and_reschedule(_mask);
//            }
//        }
//    };
//
//public:
//    static constexpr
//    uint8_t thread_mask() {
//        constexpr uint8_t previous_mask = PreviousTask::thread_mask();
//        static_assert(previous_mask != 0x80u, "Attempt to create 9th task");
//        return previous_mask << 1;
//    }
//
//
//    static
//    void execution() {
//
//    }
//};
//
//
//class Scheduler: public BaseScheduler {
//    Task task_1;
//    Task2 task_2;
//
//
//public:
//
//    template<class>
//    uint8_t constexpr task_id() {
//        return 0;
//    }
//
//    static
//    void schedule() {
//        uint8_t ready_mask = _ready_mask;
//        if(Task::thread_mask() & ready_mask) {
//            Task::run();
//            return;
//        }
//        if(Task2::thread_mask() & ready_mask) {
//            Task2::run();
//            return;
//        }
//    }
//
//    void run_task() {
//
//    }
//};

class BaseScheduler {
public:
    static volatile uint8_t _ready_mask;
    static volatile uint8_t _current_thread;

public:
    
    using TaskId = uint8_t;
    using TaskMask = uint8_t;
    
    static
    void block_and_reschedule(TaskMask block) {
        _ready_mask = block;
        asm volatile("BLOCK AND RESH %0"::"r"(_ready_mask));
    }
    
    static
    void unblock_and_reschedule(TaskMask block) {
        _ready_mask = block;
        asm volatile("UNBLOCK AND RESH %0"::"r"(_ready_mask));
    }
    
    static
    void unblock(uint8_t block) {
    }
};

volatile uint8_t BaseScheduler::_ready_mask = 0x0;

class AbstractTaskEnvironment {
public:
    using TaskId = BaseScheduler::TaskId;
    using TaskMask = BaseScheduler::TaskMask;

private:
    static constexpr
    TaskMask _higher_task_mask(TaskMask mask) {
        return mask == 0x01u ? 0x01u : mask | _higher_task_mask(mask >> 1);
    }
    
public:
    /**
     * Task id is sequential number of task.
     * Task with lower id has higher priority and will be guaranty scheduled if it is ready
     * @return sequentiol number from 1 up to scheduler limit
     */
    static constexpr
    TaskId task_id() {
        return 2;
    }
    
    /**
     * Mask of task in scheduler task list
     * @return
     */
    static constexpr
    TaskMask task_mask() {
        static_assert(task_id() <= sizeof(TaskMask) * 8, "Task count limit");
        return 0x1u << task_id();
    }
    
    static constexpr
    TaskMask higher_task_mask() {
        return _higher_task_mask(task_mask() >> 1);
    }
    
    /** Allow to reschedule another task */
    void yield();
    
    /**
     * Block execution until next unblock will call and reschedule
     */
    static
    void block();
    
    /**
     * Unblock and allow to reschedule
     */
    void unblock();
    
    /**
     * Try to reschedule in assumption that new task was unblocked by some event
     */
    void reschedule();
    
    /**
     * Unblock task according mask without reschedule
     *
     * @param mask
     */
    void unlock(TaskMask mask);
    
    /**
     * Unblock task according mask and try to reschedule only if more priority task was ublocked
     * by this call
     */
    void unblock_and_reschedule_only_unblocked(TaskMask mask) {
        unlock(mask);
        if (mask & higher_task_mask()) {
            reschedule();
        }
    }
};

/**
 * Task synchronization non recursive mutex.
 *
 * Recursive behaviour is undefined.
 */
class Mutex {
    volatile uint8_t _mutex_mask = 0x0;
public:
    using TaskMask = BaseScheduler::TaskMask;
    
    /**
     * Lock for process with mask.
     * @param mask task mask
     * @return true if lock was acquired and execution can be continue
     */
    bool lock(TaskMask mask) {
        const auto new_mask = _mutex_mask | mask;
        _mutex_mask = new_mask;
        return new_mask == mask;
    }
    
    /**
     * Try to lock
     * @param mask
     * @return true if lock was acquired and false if mutex is locked before call
     */
    bool try_lock(TaskMask mask) {
        if(_mutex_mask == 0x0) {
            _mutex_mask = mask;
            return true;
        }
        return false;
    }
    
    /**
     * Unlock.
     *
     * If mutex is not locked, behaviour is undefined
     */
    TaskMask unlock() {
        const auto mask = _mutex_mask;
        _mutex_mask = 0x0;
        return mask;
    }
};

class InterraptableEnvironment: public AbstractTaskEnvironment {
public:
    using Parent = AbstractTaskEnvironment;
    
    
    /** Atomic execution */
    class Atomic {
    public:
        explicit Atomic() {
            cli();
        }
        
        ~Atomic() {
            sei();
        }
    };
    
    static
    bool try_lock_mutex(Mutex& mutex) {
        Atomic _;
        return mutex.try_lock(task_mask());
    }
    
    static
    void lock_mutex(Mutex& mutex) {
        Atomic _;
        if (!mutex.lock(task_mask())) {
            BaseScheduler::block_and_reschedule(task_mask());
        }
    }
    
    static
    void unlock_mutex(Mutex& mutex) {
        Atomic _;
        const auto mask = mutex.unlock();
        BaseScheduler::unblock_and_reschedule(mask);
    }
  
    class MutexLock {
        Mutex& _mutex;
    public:
        explicit MutexLock(Mutex& mutex): _mutex(mutex) {
            lock_mutex(mutex);
        }
        ~MutexLock() {
            unlock_mutex(_mutex);
        }
    };
};


Mutex m;

using TaskId = uint8_t;
using TaskMask = uint8_t;
const uint8_t default_task_stack_size = 64;
using TaskFunction = void(*)();


inline __attribute__((always_inline))
void inline_global_reschedule();


template<class T, uint8_t t_stack_size=default_task_stack_size>
class TaskWithStack {
public:
    static
    uint8_t* _stack_storage()
    {
        static uint8_t storage[_stack_size];
        return storage;
    }
    
    static
    uint16_t& _stack_pointer_storage() {
        static uint16_t storage = 0;
        return storage;
    }
    
public:
    static constexpr uint8_t _stack_size = t_stack_size;
    static constexpr bool is_empty_task = false;
    
    /**
     * Init stack and put start address to stack.
     *
     * After initialization stack will contains start address and stack pointer will
     * be point to next free element on stack.
     *
     * In this case context switch will run start_task immediately after switching
     */
    static
    void init_stack(TaskFunction task) {
        uint16_t start_add = reinterpret_cast<uint16_t>(task);
        _stack_storage()[_stack_size - 1] = start_add;
        _stack_storage()[_stack_size - 2] = start_add >> 8;
        _stack_pointer_storage() = reinterpret_cast<uint16_t>(_stack_storage() + _stack_size - 3);
    }
    
    /** Highest stack address, initial value of stack */
    static constexpr
    uint16_t stack_bottom()
    {
        return stack_top() + _stack_size - 1;
    }
    
    /** Top of stack, last address which can be used on stask */
    static constexpr
    uint16_t stack_top()
    {
        return reinterpret_cast<uint16_t>(_stack_storage());
    }
    
    /** Current stack value that was saved */
    static
    uint16_t stack()
    {
        return _stack_pointer_storage();
    }
    
    /** Set current stack pointer */
    static
    void set_stack(uint16_t pointer) {
        _stack_pointer_storage() = pointer;
    }
    
    [[noreturn]] static __attribute__ ((OS_task))
    void _initial_start()
    {
        T::task();
    }
    
    static inline __attribute__((always_inline))
    void yield()
    {
        asm volatile(
        // save status reg
        "in r24, __SREG__\n\t"
        "push r24\n\t"
        "CALL %x0\n\t"
        // read status reg
        "pop r24\n\t"
        "out __SREG__, r24\n\t"
        // restore zero register
        "clr __zero_reg__\n\t"
        ::
        "s"(reschedule)
        :
        "r0", "r1",
        "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "r16", "r17",
        "r28", "r29"
        );
    }
    
    static
    void reschedule()
    {
        _stack_pointer_storage() = SP;
        inline_global_reschedule();
    }
};



class InitialTask {
};

template<class PreviousTask=InitialTask>
class TaskWithIdentifier {
public:
    static_assert(PreviousTask::task_id() <= sizeof(TaskMask) * 8, "Out of task mask");
    
    static constexpr
    TaskId task_id() {
        return PreviousTask::task_id() + 1;
    }
    
    static constexpr
    TaskMask task_mask() {
        static_assert(task_id() <= sizeof(TaskMask) * 8, "Task count limit");
        return 0x1u << task_id();
    }
};

template<>
class TaskWithIdentifier<InitialTask> {
public:
    static constexpr
    TaskId task_id() {
        return 0;
    }
    
    static constexpr
    TaskMask task_mask() {
        static_assert(task_id() <= sizeof(TaskMask) * 8, "Task count limit");
        return 0x1u << task_id();
    }
};

class FirstTask: public TaskWithStack<FirstTask>, public TaskWithIdentifier<> {
public:
    [[noreturn]]
    static
    void task()
    {
        while(true) {
            INFO("WOW RUN FIRST");
            BaseScheduler::_ready_mask = 0x02u;
            yield();
            INFO("WOW CONTINUE FIRST");
        }
    }
};

class SecondTask: public TaskWithStack<SecondTask>, public TaskWithIdentifier<FirstTask> {
public:
    [[noreturn]]
    static
    void task()
    {
        while(true) {
            INFO("WOW RUN SECOND");
            BaseScheduler::_ready_mask = 0x03u;
            yield();
            INFO("WOW CONTINUE SECOND");
        }
    }
};

class ThirdTask: public TaskWithStack<ThirdTask>, public TaskWithIdentifier<SecondTask> {
public:
    [[noreturn]]
    static
    void task()
    {
        while(true) {
            yield();
        }
    }
};

class EmptyTask {
public:
    static constexpr bool is_empty_task = true;
    
    static
    void init_stack(TaskFunction task) {}
    
    static void _initial_start() {}
    
    static constexpr
    TaskMask task_mask() {
        return 0;
    }
    
    static constexpr
    uint16_t stack() {
        return 0;
    }
};

template<class T1=EmptyTask, class T2=EmptyTask, class T3=EmptyTask, class T4=EmptyTask,
        class T5=EmptyTask, class T6=EmptyTask, class T7=EmptyTask, class T8=EmptyTask>
class Schedule: public BaseScheduler {
    
    template<class T> static
    void _init_task() {
        if(!T::is_empty_task) {
            T::init_stack(T::_initial_start);
        }
    }
public:
    static
    void init()
    {
        _init_task<T1>();
        _init_task<T2>();
        _init_task<T3>();
        _init_task<T4>();
        _init_task<T5>();
        _init_task<T6>();
        _init_task<T7>();
        _init_task<T8>();
    }
    
    inline __attribute__((always_inline))
    static
    void schedule()
    {
        while(true) {
            const auto mask = BaseScheduler::_ready_mask;
            if(mask & T1::task_mask()) {
                SP = T1::stack();
                return;
            }
            if(mask & T2::task_mask()) {
                SP = T2::stack();
                return;
            }
            if(mask & T3::task_mask()) {
                SP = T3::stack();
                return;
            }
            if(mask & T4::task_mask()) {
                SP = T4::stack();
                return;
            }
            if(mask & T5::task_mask()) {
                SP = T5::stack();
                return;
            }
            if(mask & T6::task_mask()) {
                SP = T6::stack();
                return;
            }
            if(mask & T7::task_mask()) {
                SP = T7::stack();
                return;
            }
            if(mask & T8::task_mask()) {
                SP = T8::stack();
                return;
            }
        }
    }
    
    static
    void run()
    {
        schedule();
    }
};

using Sh = Schedule<FirstTask, SecondTask, ThirdTask>;

void inline_global_reschedule()
{
    Sh::schedule();
}

int main() {
    Sh::init();
    Sh::_ready_mask = 0x01;
    Sh::run();
}