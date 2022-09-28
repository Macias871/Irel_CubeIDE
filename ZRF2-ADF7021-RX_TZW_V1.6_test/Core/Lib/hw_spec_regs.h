#ifndef HW_SPEC_REGS_H_
#define HW_SPEC_REGS_H_

// PRIMASK - Register to mask out configurable exceptions

#define PRIMASK_MASK_EXCEPTIONS_bit			0
#define PRIMASK_MASK_EXCEPTIONS				(1 << PRIMASK_MASK_EXCEPTIONS_bit)

// FAULTMASK - Register to raise priority to the HardFault level

#define FAULTMASK_MASK_EXCEPTIONS_bit		0
#define FAULTMASK_MASK_EXCEPTIONS			(1 << FAULTMASK_MASK_EXCEPTIONS_bit)

// CONTROL - The special-purpose control register

#define CONTROL_THREAD_UNPRIVILEGED_bit		0
#define CONTROL_ALTERNATE_STACK_bit			1

#define CONTROL_THREAD_UNPRIVILEGED			(1 << CONTROL_THREAD_UNPRIVILEGED_bit)
#define CONTROL_ALTERNATE_STACK				(1 << CONTROL_ALTERNATE_STACK_bit)

#endif /* HW_SPEC_REGS_H_ */
