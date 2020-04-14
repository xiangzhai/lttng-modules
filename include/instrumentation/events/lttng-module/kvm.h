/* SPDX-License-Identifier: GPL-2.0-only */
#if !defined(LTTNG_TRACE_KVM_MAIN_H) || defined(TRACE_HEADER_MULTI_READ)
#define LTTNG_TRACE_KVM_MAIN_H

#include <lttng/lttng-tracepoint-event.h>

#undef TRACE_SYSTEM
#define TRACE_SYSTEM kvm

LTTNG_TRACEPOINT_EVENT(kvm_userspace_exit,
	    TP_PROTO(__u32 reason, int errno),
	    TP_ARGS(reason, errno),

	TP_FIELDS(
		ctf_integer(__u32, reason, reason)
		ctf_integer(int, errno, errno)
	)
)

#if defined(__KVM_HAVE_IRQ_LINE)
LTTNG_TRACEPOINT_EVENT(kvm_set_irq,
	TP_PROTO(unsigned int gsi, int level, int irq_source_id),
	TP_ARGS(gsi, level, irq_source_id),

	TP_FIELDS(
		ctf_integer(unsigned int, gsi, gsi)
		ctf_integer(int, level, level)
		ctf_integer(int, irq_source_id, irq_source_id)
	)
)
#endif

#if defined(__KVM_HAVE_IOAPIC)

LTTNG_TRACEPOINT_EVENT(kvm_ioapic_set_irq,
	    TP_PROTO(__u64 e, int pin, bool coalesced),
	    TP_ARGS(e, pin, coalesced),

	TP_FIELDS(
		ctf_integer(__u64, e, e)
		ctf_integer(int, pin, pin)
		ctf_integer(bool, coalesced, coalesced)
	)
)

LTTNG_TRACEPOINT_EVENT(kvm_msi_set_irq,
	    TP_PROTO(__u64 address, __u64 data),
	    TP_ARGS(address, data),

	TP_FIELDS(
		ctf_integer_hex(__u64, address, address)
		ctf_integer(__u64, data, data)
	)
)

LTTNG_TRACEPOINT_EVENT(kvm_ack_irq,
	TP_PROTO(unsigned int irqchip, unsigned int pin),
	TP_ARGS(irqchip, pin),

	TP_FIELDS(
		ctf_integer(unsigned int, irqchip, irqchip)
		ctf_integer(unsigned int, pin, pin)
	)
)

#endif /* defined(__KVM_HAVE_IOAPIC) */

#define KVM_TRACE_MMIO_READ_UNSATISFIED 0
#define KVM_TRACE_MMIO_READ 1
#define KVM_TRACE_MMIO_WRITE 2

#define kvm_trace_symbol_mmio \
	{ KVM_TRACE_MMIO_READ_UNSATISFIED, "unsatisfied-read" }, \
	{ KVM_TRACE_MMIO_READ, "read" }, \
	{ KVM_TRACE_MMIO_WRITE, "write" }


LTTNG_TRACEPOINT_EVENT(kvm_mmio,
	TP_PROTO(int type, int len, u64 gpa, void *val),
	TP_ARGS(type, len, gpa, val),

	TP_FIELDS(
		ctf_integer(u32, type, type)
		ctf_integer(u32, len, len)
		ctf_integer(u64, gpa, gpa)
		ctf_sequence_hex(unsigned char, val, val, u32, len)
	)
)

#define kvm_fpu_load_symbol	\
	{0, "unload"},		\
	{1, "load"}

LTTNG_TRACEPOINT_EVENT(kvm_fpu,
	TP_PROTO(int load),
	TP_ARGS(load),

	TP_FIELDS(
		ctf_integer(u32, load, load)
	)
)

LTTNG_TRACEPOINT_EVENT(kvm_age_page,
	TP_PROTO(ulong gfn, int level, struct kvm_memory_slot *slot, int ref),
	TP_ARGS(gfn, level, slot, ref),

	TP_FIELDS(
		ctf_integer(u64, hva,
			((gfn - slot->base_gfn) << PAGE_SHIFT) + slot->userspace_addr)
		ctf_integer(u64, gfn, gfn)
		ctf_integer(u8, level, level)
		ctf_integer(u8, referenced, ref)
	)
)

#ifdef CONFIG_KVM_ASYNC_PF
LTTNG_TRACEPOINT_EVENT_CLASS(kvm_async_get_page_class,

	TP_PROTO(u64 gva, u64 gfn),

	TP_ARGS(gva, gfn),

	TP_FIELDS(
		ctf_integer(__u64, gva, gva)
		ctf_integer(u64, gfn, gfn)
	)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(kvm_async_get_page_class, kvm_try_async_get_page,

	TP_PROTO(u64 gva, u64 gfn),

	TP_ARGS(gva, gfn)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(kvm_async_get_page_class, kvm_async_pf_doublefault,

	TP_PROTO(u64 gva, u64 gfn),

	TP_ARGS(gva, gfn)
)

LTTNG_TRACEPOINT_EVENT_CLASS(kvm_async_pf_nopresent_ready,

	TP_PROTO(u64 token, u64 gva),

	TP_ARGS(token, gva),

	TP_FIELDS(
		ctf_integer(__u64, token, token)
		ctf_integer(__u64, gva, gva)
	)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(kvm_async_pf_nopresent_ready, kvm_async_pf_not_present,

	TP_PROTO(u64 token, u64 gva),

	TP_ARGS(token, gva)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(kvm_async_pf_nopresent_ready, kvm_async_pf_ready,

	TP_PROTO(u64 token, u64 gva),

	TP_ARGS(token, gva)
)

LTTNG_TRACEPOINT_EVENT(
	kvm_async_pf_completed,
	TP_PROTO(unsigned long address, u64 gva),
	TP_ARGS(address, gva),

	TP_FIELDS(
		ctf_integer_hex(unsigned long, address, address)
		ctf_integer(u64, gva, gva)
	)
)

#endif

#endif /* LTTNG_TRACE_KVM_MAIN_H */

/* This part must be outside protection */
#include <lttng/define_trace.h>