#ifndef _VMX_INTERCEPT_H
#define _VMX_INTERCEPT_H

#include <xen/config.h>
#include <xen/init.h>
#include <xen/lib.h>
#include <xen/time.h>
#include <xen/errno.h>
#include <public/io/ioreq.h>

#define MAX_IO_HANDLER              4

#define VMX_PORTIO                  0
#define VMX_MMIO                    1

typedef int (*intercept_action_t)(ioreq_t *);

struct io_handler {
    int                 type;
    unsigned long       addr;
    unsigned long       size;
    intercept_action_t  action;
};

struct vmx_io_handler {
    int     num_slot;
    struct  io_handler hdl_list[MAX_IO_HANDLER];
};

/* global io interception point in HV */
extern int vmx_io_intercept(ioreq_t *p, int type);
extern int register_io_handler(unsigned long addr, unsigned long size,
                               intercept_action_t action, int type);

static inline int vmx_portio_intercept(ioreq_t *p)
{
    return vmx_io_intercept(p, VMX_PORTIO);
}

static inline int vmx_mmio_intercept(ioreq_t *p)
{
    return vmx_io_intercept(p, VMX_MMIO);
}

static inline int register_portio_handler(unsigned long addr,
                                          unsigned long size,
                                          intercept_action_t action)
{
    return register_io_handler(addr, size, action, VMX_PORTIO);
}

static inline int register_mmio_handler(unsigned long addr,
                                        unsigned long size,
                                        intercept_action_t action)
{
    return register_io_handler(addr, size, action, VMX_MMIO);
}

#endif /* _VMX_INTERCEPT_H */
