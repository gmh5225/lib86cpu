/*
 * the register file
 *
 * ergo720                Copyright (c) 2019
 * the libcpu developers  Copyright (c) 2009-2010
 */


#define DEFINE_REG32(_reg)			\
	struct {				\
		uint32_t		_reg;	\
	}

#define DEFINE_REG16(_reg)			\
	struct {				\
		uint16_t		_reg;	\
	}

#define DEFINE_SEG_REG(_reg)			\
	struct {				\
		uint16_t		_reg;	\
		struct { \
			uint32_t base; \
			uint32_t limit; \
			uint32_t flags; \
		} _reg ## _hidden; \
	}

#define DEFINE_FP80(_reg) \
	PACKED(struct { \
		uint64_t low; \
		uint16_t high; \
	} _reg;)

// These registers must have the same order they have in cpu->regs_layout
struct regs_t {
	/* General registers */
	DEFINE_REG32(eax);
	DEFINE_REG32(ecx);
	DEFINE_REG32(edx);
	DEFINE_REG32(ebx);
	/* Pointer registers */
	DEFINE_REG32(esp);
	DEFINE_REG32(ebp);
	/* Index registers */
	DEFINE_REG32(esi);
	DEFINE_REG32(edi);

	/* Segment registers */
	DEFINE_SEG_REG(es);
	DEFINE_SEG_REG(cs);
	DEFINE_SEG_REG(ss);
	DEFINE_SEG_REG(ds);
	DEFINE_SEG_REG(fs);
	DEFINE_SEG_REG(gs);

	/* Control registers */
	DEFINE_REG32(cr0);
	DEFINE_REG32(cr1);
	DEFINE_REG32(cr2);
	DEFINE_REG32(cr3);
	DEFINE_REG32(cr4);

	/* Debug registers */
	DEFINE_REG32(dr0);
	DEFINE_REG32(dr1);
	DEFINE_REG32(dr2);
	DEFINE_REG32(dr3);
	DEFINE_REG32(dr4);
	DEFINE_REG32(dr5);
	DEFINE_REG32(dr6);
	DEFINE_REG32(dr7);

	DEFINE_REG32(eflags);
	DEFINE_REG32(eip);

	/* Memory management registers */
	DEFINE_SEG_REG(idtr); // selector and flags unused
	DEFINE_SEG_REG(gdtr); // selector and flags unused
	DEFINE_SEG_REG(ldtr);
	DEFINE_SEG_REG(tr);

	/* Fpu registers */
	DEFINE_FP80(r0);
	DEFINE_FP80(r1);
	DEFINE_FP80(r2);
	DEFINE_FP80(r3);
	DEFINE_FP80(r4);
	DEFINE_FP80(r5);
	DEFINE_FP80(r6);
	DEFINE_FP80(r7);
	DEFINE_REG16(status);
	DEFINE_REG16(tag);
};
