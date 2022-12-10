/*
 * x86 function prototypes and internal variables
 *
 * ergo720                Copyright (c) 2019
 */

#pragma once

#include "decode.h"
#include "support.h"
#include "breakpoint.h"


template<bool remove_hook = false, bool is_virt = true>
void tc_invalidate(cpu_ctx_t * cpu_ctx, addr_t addr, [[maybe_unused]] uint8_t size = 0, [[maybe_unused]] uint32_t eip = 0);
template<bool should_flush_tlb>
void tc_should_clear_cache_and_tlb(cpu_t *cpu, addr_t start, addr_t end);
void tc_cache_clear(cpu_t *cpu);
void tc_cache_purge(cpu_t *cpu);
addr_t get_pc(cpu_ctx_t *cpu_ctx);
template<bool is_int = false> translated_code_t *cpu_raise_exception(cpu_ctx_t *cpu_ctx);
translated_code_t *cpu_do_int(cpu_ctx_t *cpu_ctx, uint32_t int_flg);

// cpu hidden flags (assumed to be constant during exec of a tc, together with a flag subset of eflags)
// HFLG_CPL: cpl of cpu
// HFLG_CS32: 16 or 32 bit code segment
// HFLG_SS32: 16 or 32 bit stack segment
// HFLG_PE_MODE: real or protected mode
// HFLG_CR0_EM: em flag of cr0
// HFLG_TRAMP: used to select the trampoline tc instead of the hook tc
// HFLG_DBG_TRAP: used to suppress data/io watchpoints (not recorded in the tc flags)
#define CPL_SHIFT       0
#define CS32_SHIFT      2
#define SS32_SHIFT      3
#define PE_MODE_SHIFT   4
#define EM_SHIFT        5
#define TRAMP_SHIFT     6
#define DBG_TRAP_SHIFT  7
#define HFLG_CPL        (3 << CPL_SHIFT)
#define HFLG_CS32       (1 << CS32_SHIFT)
#define HFLG_SS32       (1 << SS32_SHIFT)
#define HFLG_PE_MODE    (1 << PE_MODE_SHIFT)
#define HFLG_CR0_EM     (1 << EM_SHIFT)
#define HFLG_TRAMP      (1 << TRAMP_SHIFT)
#define HFLG_DBG_TRAP   (1 << DBG_TRAP_SHIFT)
#define HFLG_CONST      (HFLG_CPL | HFLG_CS32 | HFLG_SS32 | HFLG_PE_MODE | HFLG_CR0_EM | HFLG_TRAMP)

// cpu interrupt flags
#define CPU_HW_INT      (1 << 0)
#define CPU_ABORT_INT   (1 << 1)
#define CPU_A20_INT     (1 << 2)
#define CPU_REGION_INT  (1 << 3)
#define CPU_PAUSE_INT   (1 << 4)

// disassembly context flags
#define DISAS_FLG_CS32         (1 << 0)
#define DISAS_FLG_PAGE_CROSS   (1 << 2)
#define DISAS_FLG_FETCH_FAULT  DISAS_FLG_PAGE_CROSS
#define DISAS_FLG_DBG_FAULT    DISAS_FLG_PAGE_CROSS
#define DISAS_FLG_ONE_INSTR    CPU_DISAS_ONE

// tc struct flags/offsets
#define TC_JMP_DST_PC     0
#define TC_JMP_NEXT_PC    1
#define TC_JMP_RET        2
#define TC_FLG_NUM_JMP         (3 << 0)
#define TC_FLG_INDIRECT        (1 << 2)
#define TC_FLG_DIRECT          (1 << 3)
#define TC_FLG_JMP_TAKEN       (3 << 4)
#define TC_FLG_RET             (1 << 6)
#define TC_FLG_DST_ONLY        (1 << 7)  // jump(dest_pc)
#define TC_FLG_LINK_MASK  (TC_FLG_INDIRECT | TC_FLG_DIRECT | TC_FLG_RET | TC_FLG_DST_ONLY)

// segment descriptor flags
#define SEG_DESC_TY   (15ULL << 40) // type
#define SEG_DESC_TYC  (3ULL << 42)  // type/conf bits
#define SEG_DESC_DCRW (5ULL << 41)  // data/code read/write
#define SEG_DESC_A    (1ULL << 40)  // accessed
#define SEG_DESC_W    (1ULL << 41)  // write, data desc
#define SEG_DESC_R    SEG_DESC_W    // read, code desc
#define SEG_DESC_BY   SEG_DESC_W    // busy
#define SEG_DESC_C    (1ULL << 42)  // conforming
#define SEG_DESC_DC   (1ULL << 43)  // data/code
#define SEG_DESC_S    (1ULL << 44)  // system
#define SEG_DESC_DPL  (3ULL << 45)  // dpl
#define SEG_DESC_P    (1ULL << 47)  // present
#define SEG_DESC_DB   (1ULL << 54)  // default size
#define SEG_DESC_G    (1ULL << 55)  // granularity
#define SEG_DESC_TSS16AV  1         // system / tss, 16 bit, available
#define SEG_DESC_LDT      2         // system / ldt
#define SEG_DESC_TSS32AV  9         // system / tss, 32 bit, available

// segment hidden flags
#define SEG_HIDDEN_DB      (1 << 22)  // default size
#define SEG_HIDDEN_TSS_TY  (1 << 11)  // 16/32 tss type

#define EAX_idx     0
#define ECX_idx     1
#define EDX_idx     2
#define EBX_idx     3
#define ESP_idx     4
#define EBP_idx     5
#define ESI_idx     6
#define EDI_idx     7
#define ES_idx      8
#define CS_idx      9
#define SS_idx      10
#define DS_idx      11
#define FS_idx      12
#define GS_idx      13
#define CR0_idx     14
#define CR1_idx     15
#define CR2_idx     16
#define CR3_idx     17
#define CR4_idx     18
#define DR0_idx     19
#define DR1_idx     20
#define DR2_idx     21
#define DR3_idx     22
#define DR4_idx     23
#define DR5_idx     24
#define DR6_idx     25
#define DR7_idx     26
#define EFLAGS_idx  27
#define EIP_idx     28
#define IDTR_idx    29
#define GDTR_idx    30
#define LDTR_idx    31
#define TR_idx      32
#define R0_idx      33
#define R1_idx      34
#define R2_idx      35
#define R3_idx      36
#define R4_idx      37
#define R5_idx      38
#define R6_idx      39
#define R7_idx      40
#define ST_idx      41
#define TAG_idx     42

#define SEG_offset  ES_idx
#define CR_offset   CR0_idx
#define DR_offset   DR0_idx

#define SEG_SEL_idx     0
#define SEG_HIDDEN_idx  1
#define SEG_BASE_idx    0
#define SEG_LIMIT_idx   1
#define SEG_FLG_idx     2
#define F80_LOW_idx     0
#define F80_HIGH_idx    1

// eflags macros
#define TF_MASK        (1 << 8)
#define IF_MASK        (1 << 9)
#define DF_MASK        (1 << 10)
#define IOPL_MASK      (3 << 12)
#define NT_MASK        (1 << 14)
#define RF_MASK        (1 << 16)
#define VM_MASK        (1 << 17)
#define AC_MASK        (1 << 18)
#define VIF_MASK       (1 << 19)
#define VIP_MASK       (1 << 20)
#define ID_MASK        (1 << 21)
#define EFLAGS_CONST   (TF_MASK | IOPL_MASK | RF_MASK | AC_MASK)

// exception numbers
#define EXP_DE  0   // divide error
#define EXP_DB  1   // debug
#define EXP_NMI 2   // non-maskable interrupt
#define EXP_BP  3   // breakpoint
#define EXP_OF  4   // overflow
#define EXP_BR  5   // bound range exceeded
#define EXP_UD  6   // invalid opcode
#define EXP_NM  7   // no math coprocessor
#define EXP_DF  8   // double fault
#define EXP_TS  10  // invalid TSS
#define EXP_NP  11  // segment not present
#define EXP_SS  12  // stack segment fault
#define EXP_GP  13  // general protection
#define EXP_PF  14  // page fault
#define EXP_MF  16  // math fault
#define EXP_AC  17  // alignment check
#define EXP_MC  18  // machine check
#define EXP_XF  19  // SIMD floating point exception
#define EXP_INVALID 0xFFFF

// pte flags
#define PTE_PRESENT   (1 << 0)
#define PTE_WRITE     (1 << 1)
#define PTE_USER      (1 << 2)
#define PTE_ACCESSED  (1 << 5)
#define PTE_DIRTY     (1 << 6)
#define PTE_LARGE     (1 << 7)
#define PTE_GLOBAL    (1 << 8)
#define PTE_ADDR_4K   0xFFFFF000
#define PTE_ADDR_4M   0xFFC00000

// page macros
#define PAGE_SHIFT        12
#define PAGE_SHIFT_LARGE  22
#define PAGE_SIZE         (1 << PAGE_SHIFT)
#define PAGE_SIZE_LARGE   (1 << PAGE_SHIFT_LARGE)
#define PAGE_MASK         (PAGE_SIZE - 1)
#define PAGE_MASK_LARGE   (PAGE_SIZE_LARGE - 1)

// tlb macros
#define TLB_SUP_READ    (1 << 0)  // page access type allowed: supervisor read
#define TLB_SUP_WRITE   (1 << 1)  // page access type allowed: supervisor write
#define TLB_USER_READ   (1 << 2)  // page access type allowed: user read
#define TLB_USER_WRITE  (1 << 3)  // page access type allowed: user write
#define TLB_CODE        (1 << 4)  // page contains at least one code block
#define TLB_RAM         (1 << 5)  // page is backed by ram
#define TLB_ROM         (1 << 6)  // page is backed by rom
#define TLB_MMIO        (1 << 7)  // page is backed by mmio
#define TLB_GLOBAL      (1 << 8)  // page has global flag in its pte
#define TLB_DIRTY       (1 << 9)  // page was written to at least once
#define TLB_WATCH       (1 << 10) // page has at least one debug watchpoint
#define TLB_SUBPAGE     (1 << 11) // page is backed by different memory regions
#define TLB_VALID       (TLB_SUP_READ | TLB_SUP_WRITE | TLB_USER_READ | TLB_USER_WRITE) // entry is valid
#define TLB_zero        0
#define TLB_keep_cw     1
#define TLB_no_g        2

// control register flags
#define CR0_PG_MASK (1 << 31)
#define CR0_CD_MASK (1 << 30)
#define CR0_NW_MASK (1 << 29)
#define CR0_AM_MASK (1 << 18)
#define CR0_WP_MASK (1 << 16)
#define CR0_NE_MASK (1 << 5)
#define CR0_ET_MASK (1 << 4)
#define CR0_TS_MASK (1 << 3)
#define CR0_EM_MASK (1 << 2)
#define CR0_MP_MASK (1 << 1)
#define CR0_PE_MASK (1 << 0)
#define CR0_FLG_MASK (CR0_PG_MASK | CR0_CD_MASK | CR0_NW_MASK | CR0_AM_MASK | CR0_WP_MASK | CR0_NE_MASK | CR0_ET_MASK |\
CR0_TS_MASK | CR0_EM_MASK | CR0_MP_MASK | CR0_PE_MASK)
#define CR3_PD_MASK 0xFFFFF000
#define CR3_PCD_MASK (1 << 4)
#define CR3_PWT_MASK (1 << 3)
#define CR3_FLG_MASK (CR3_PD_MASK | CR3_PCD_MASK | CR3_PWT_MASK)
#define CR4_VME_MASK (1 << 0)
#define CR4_TSD_MASK (1 << 2)
#define CR4_DE_MASK  (1 << 3)
#define CR4_PSE_MASK (1 << 4)
#define CR4_PAE_MASK (1 << 5)
#define CR4_PGE_MASK (1 << 7)
#define CR4_RES_MASK (0x1FFFFF << 11) // cr4 reserved bits

// debug register flags
#define DR6_B0_MASK      (1 << 0)
#define DR6_B1_MASK      (1 << 1)
#define DR6_B2_MASK      (1 << 2)
#define DR6_B3_MASK      (1 << 3)
#define DR6_BD_MASK      (1 << 13)
#define DR6_BS_MASK      (1 << 14)
#define DR6_RES_MASK     0xFFFF0FF0 // dr6 reserved bits
#define DR7_GD_MASK      (1 << 13)
#define DR7_RES_MASK     0x400 // dr7 reserved bits
#define DR7_TYPE_SHIFT   16
#define DR7_LEN_SHIFT    18
#define DR7_TYPE_INSTR   0
#define DR7_TYPE_DATA_W  1
#define DR7_TYPE_IO_RW   2
#define DR7_TYPE_DATA_RW 3

// fpu register flags
#define ST_ES_MASK  (1 << 7)
#define ST_TOP_MASK (3 << 11)

// msr register addresses
#define IA32_APIC_BASE             0x1B
#define IA32_MTRRCAP               0xFE
#define IA32_MTRR_PHYSBASE_base    0x200
#define IA32_MTRR_PHYSMASK_base    0x201
#define IA32_MTRR_FIX64K_00000     0x250
#define IA32_MTRR_FIX16K_80000     0x258
#define IA32_MTRR_FIX16K_A0000     0x259
#define IA32_MTRR_FIX4K_C0000      0x268
#define IA32_MTRR_FIX4K_C8000      0x269
#define IA32_MTRR_FIX4K_D0000      0x26A
#define IA32_MTRR_FIX4K_D8000      0x26B
#define IA32_MTRR_FIX4K_E0000      0x26C
#define IA32_MTRR_FIX4K_E8000      0x26D
#define IA32_MTRR_FIX4K_F0000      0x26E
#define IA32_MTRR_FIX4K_F8000      0x26F
#define IA32_MTRR_DEF_TYPE         0x2FF
#define IA32_MTRR_PHYSBASE(n)      (IA32_MTRR_PHYSBASE_base + (n * 2))
#define IA32_MTRR_PHYSMASK(n)      (IA32_MTRR_PHYSMASK_base + (n * 2))

// msr macros
#define MSR_IA32_APICBASE_BSP      (1 << 8)
#define MSR_MTRRcap_VCNT           8
#define MSR_MTRRcap_FIX            (1 << 8)
#define MSR_MTRRcap_WC             (1 << 10)
#define MSR_IA32_APIC_BASE_RES     0xFFFFFFF0000006FF
#define MSR_MTRR_PHYSBASE_RES      0xFFFFFFF000000F00
#define MSR_MTRR_PHYSMASK_RES      0xFFFFFFF0000007FF
#define MSR_MTRR_DEF_TYPE_RES      0xFFFFFFFFFFFFF300

#define X86_MAX_INSTR_LENGTH 15
