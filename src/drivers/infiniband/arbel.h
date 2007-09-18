#ifndef _ARBEL_H
#define _ARBEL_H

/** @file
 *
 * Mellanox Arbel Infiniband HCA driver
 *
 */

#include <stdint.h>
#include <gpxe/uaccess.h>
#include "mlx_bitops.h"
#include "MT25218_PRM.h"

/*
 * Hardware constants
 *
 */

/* PCI BARs */
#define ARBEL_PCI_CONFIG_BAR		PCI_BASE_ADDRESS_0
#define ARBEL_PCI_CONFIG_BAR_SIZE	0x100000
#define ARBEL_PCI_UAR_BAR		PCI_BASE_ADDRESS_2
#define ARBEL_PCI_UAR_IDX		1
#define ARBEL_PCI_UAR_SIZE		0x1000

/* UAR context table (UCE) resource types */
#define ARBEL_UAR_RES_NONE		0x00
#define ARBEL_UAR_RES_CQ_CI		0x01
#define ARBEL_UAR_RES_CQ_ARM		0x02
#define ARBEL_UAR_RES_SQ		0x03
#define ARBEL_UAR_RES_RQ		0x04
#define ARBEL_UAR_RES_GROUP_SEP		0x07

/* Work queue entry and completion queue entry opcodes */
#define ARBEL_OPCODE_SEND		0x0a
#define ARBEL_OPCODE_RECV_ERROR		0xfe
#define ARBEL_OPCODE_SEND_ERROR		0xff

/* HCA command register opcodes */
#define ARBEL_HCR_QUERY_DEV_LIM		0x0003
#define ARBEL_HCR_QUERY_FW		0x0004
#define ARBEL_HCR_INIT_HCA		0x0007
#define ARBEL_HCR_CLOSE_HCA		0x0008
#define ARBEL_HCR_INIT_IB		0x0009
#define ARBEL_HCR_CLOSE_IB		0x000a
#define ARBEL_HCR_SW2HW_MPT		0x000d
#define ARBEL_HCR_MAP_EQ		0x0012
#define ARBEL_HCR_SW2HW_EQ		0x0013
#define ARBEL_HCR_HW2SW_EQ		0x0014
#define ARBEL_HCR_SW2HW_CQ		0x0016
#define ARBEL_HCR_HW2SW_CQ		0x0017
#define ARBEL_HCR_RST2INIT_QPEE		0x0019
#define ARBEL_HCR_INIT2RTR_QPEE		0x001a
#define ARBEL_HCR_RTR2RTS_QPEE		0x001b
#define ARBEL_HCR_2RST_QPEE		0x0021
#define ARBEL_HCR_MAD_IFC		0x0024
#define ARBEL_HCR_READ_MGM		0x0025
#define ARBEL_HCR_WRITE_MGM		0x0026
#define ARBEL_HCR_MGID_HASH		0x0027
#define ARBEL_HCR_RUN_FW		0x0ff6
#define ARBEL_HCR_DISABLE_LAM		0x0ff7
#define ARBEL_HCR_ENABLE_LAM		0x0ff8
#define ARBEL_HCR_UNMAP_ICM		0x0ff9
#define ARBEL_HCR_MAP_ICM		0x0ffa
#define ARBEL_HCR_UNMAP_ICM_AUX		0x0ffb
#define ARBEL_HCR_MAP_ICM_AUX		0x0ffc
#define ARBEL_HCR_SET_ICM_SIZE		0x0ffd
#define ARBEL_HCR_UNMAP_FA		0x0ffe
#define ARBEL_HCR_MAP_FA		0x0fff

/* Service types */
#define ARBEL_ST_UD			0x03

/* MTUs */
#define ARBEL_MTU_2048			0x04

#define ARBEL_NO_EQ			64

#define ARBEL_INVALID_LKEY		0x00000100UL

#define ARBEL_PAGE_SIZE			4096

#define ARBEL_DB_POST_SND_OFFSET	0x10

/*
 * Datatypes that seem to be missing from the autogenerated documentation
 *
 */
struct arbelprm_mgm_hash_st {
	pseudo_bit_t reserved0[0x00020];
/* -------------- */
	pseudo_bit_t hash[0x00010];
	pseudo_bit_t reserved1[0x00010];
} __attribute__ (( packed ));

struct arbelprm_scalar_parameter_st {
	pseudo_bit_t reserved0[0x00020];
/* -------------- */
	pseudo_bit_t value[0x00020];
} __attribute__ (( packed ));

/*
 * Wrapper structures for hardware datatypes
 *
 */

struct MLX_DECLARE_STRUCT ( arbelprm_access_lam );
struct MLX_DECLARE_STRUCT ( arbelprm_completion_queue_context );
struct MLX_DECLARE_STRUCT ( arbelprm_completion_queue_entry );
struct MLX_DECLARE_STRUCT ( arbelprm_completion_with_error );
struct MLX_DECLARE_STRUCT ( arbelprm_cq_arm_db_record );
struct MLX_DECLARE_STRUCT ( arbelprm_cq_ci_db_record );
struct MLX_DECLARE_STRUCT ( arbelprm_eqc );
struct MLX_DECLARE_STRUCT ( arbelprm_hca_command_register );
struct MLX_DECLARE_STRUCT ( arbelprm_init_hca );
struct MLX_DECLARE_STRUCT ( arbelprm_init_ib );
struct MLX_DECLARE_STRUCT ( arbelprm_mad_ifc );
struct MLX_DECLARE_STRUCT ( arbelprm_mgm_entry );
struct MLX_DECLARE_STRUCT ( arbelprm_mgm_hash );
struct MLX_DECLARE_STRUCT ( arbelprm_mpt );
struct MLX_DECLARE_STRUCT ( arbelprm_qp_db_record );
struct MLX_DECLARE_STRUCT ( arbelprm_qp_ee_state_transitions );
struct MLX_DECLARE_STRUCT ( arbelprm_query_dev_lim );
struct MLX_DECLARE_STRUCT ( arbelprm_query_fw );
struct MLX_DECLARE_STRUCT ( arbelprm_queue_pair_ee_context_entry );
struct MLX_DECLARE_STRUCT ( arbelprm_recv_wqe_segment_next );
struct MLX_DECLARE_STRUCT ( arbelprm_scalar_parameter );
struct MLX_DECLARE_STRUCT ( arbelprm_send_doorbell );
struct MLX_DECLARE_STRUCT ( arbelprm_ud_address_vector );
struct MLX_DECLARE_STRUCT ( arbelprm_virtual_physical_mapping );
struct MLX_DECLARE_STRUCT ( arbelprm_wqe_segment_ctrl_send );
struct MLX_DECLARE_STRUCT ( arbelprm_wqe_segment_data_ptr );
struct MLX_DECLARE_STRUCT ( arbelprm_wqe_segment_next );
struct MLX_DECLARE_STRUCT ( arbelprm_wqe_segment_ud );

/*
 * Composite hardware datatypes
 *
 */

#define ARBEL_MAX_GATHER 1

struct arbelprm_ud_send_wqe {
	struct arbelprm_wqe_segment_next next;
	struct arbelprm_wqe_segment_ctrl_send ctrl;
	struct arbelprm_wqe_segment_ud ud;
	struct arbelprm_wqe_segment_data_ptr data[ARBEL_MAX_GATHER];
} __attribute__ (( packed ));

#define ARBEL_MAX_SCATTER 1

struct arbelprm_recv_wqe {
	/* The autogenerated header is inconsistent between send and
	 * receive WQEs.  The "ctrl" structure for receive WQEs is
	 * defined to include the "next" structure.  Since the "ctrl"
	 * part of the "ctrl" structure contains only "reserved, must
	 * be zero" bits, we ignore its definition and provide
	 * something more usable.
	 */
	struct arbelprm_recv_wqe_segment_next next;
	uint32_t ctrl[2]; /* All "reserved, must be zero" */
	struct arbelprm_wqe_segment_data_ptr data[ARBEL_MAX_SCATTER];
} __attribute__ (( packed ));

union arbelprm_completion_entry {
	struct arbelprm_completion_queue_entry normal;
	struct arbelprm_completion_with_error error;
} __attribute__ (( packed ));

union arbelprm_doorbell_record {
	struct arbelprm_cq_arm_db_record cq_arm;
	struct arbelprm_cq_ci_db_record cq_ci;
	struct arbelprm_qp_db_record qp;
} __attribute__ (( packed ));

union arbelprm_doorbell_register {
	struct arbelprm_send_doorbell send;
	uint32_t dword[2];
} __attribute__ (( packed ));

union arbelprm_mad {
	struct arbelprm_mad_ifc ifc;
	union ib_mad mad;
} __attribute__ (( packed ));

/*
 * gPXE-specific definitions
 *
 */

/** Arbel device limits */
struct arbel_dev_limits {
	/** Number of reserved QPs */
	unsigned int reserved_qps;
	/** QP context entry size */
	size_t qpc_entry_size;
	/** Extended QP context entry size */
	size_t eqpc_entry_size;
	/** Number of reserved SRQs */
	unsigned int reserved_srqs;
	/** SRQ context entry size */
	size_t srqc_entry_size;
	/** Number of reserved EEs */
	unsigned int reserved_ees;
	/** EE context entry size */
	size_t eec_entry_size;
	/** Extended EE context entry size */
	size_t eeec_entry_size;
	/** Number of reserved CQs */
	unsigned int reserved_cqs;
	/** CQ context entry size */
	size_t cqc_entry_size;
	/** Number of reserved MTTs */
	unsigned int reserved_mtts;
	/** MTT entry size */
	size_t mtt_entry_size;
	/** Number of reserved MRWs */
	unsigned int reserved_mrws;
	/** MPT entry size */
	size_t mpt_entry_size;
	/** Number of reserved RDBs */
	unsigned int reserved_rdbs;
	/** EQ context entry size */
	size_t eqc_entry_size;
	/** Number of reserved UARs */
	unsigned int reserved_uars;
};

/** Alignment of Arbel send work queue entries */
#define ARBEL_SEND_WQE_ALIGN 128

/** An Arbel send work queue entry */
union arbel_send_wqe {
	struct arbelprm_ud_send_wqe ud;
	uint8_t force_align[ARBEL_SEND_WQE_ALIGN];
} __attribute__ (( packed ));

/** An Arbel send work queue */
struct arbel_send_work_queue {
	/** Doorbell record number */
	unsigned int doorbell_idx;
	/** Work queue entries */
	union arbel_send_wqe *wqe;
	/** Size of work queue */
	size_t wqe_size;
};

/** Alignment of Arbel receive work queue entries */
#define ARBEL_RECV_WQE_ALIGN 64

/** An Arbel receive work queue entry */
union arbel_recv_wqe {
	struct arbelprm_recv_wqe recv;
	uint8_t force_align[ARBEL_RECV_WQE_ALIGN];
} __attribute__ (( packed ));

/** An Arbel receive work queue */
struct arbel_recv_work_queue {
	/** Doorbell record number */
	unsigned int doorbell_idx;
	/** Work queue entries */
	union arbel_recv_wqe *wqe;
	/** Size of work queue */
	size_t wqe_size;
};

/** Maximum number of allocatable queue pairs
 *
 * This is a policy decision, not a device limit.
 */
#define ARBEL_MAX_QPS		8

/** Base queue pair number */
#define ARBEL_QPN_BASE 0x550000

/** An Arbel queue pair */
struct arbel_queue_pair {
	/** Send work queue */
	struct arbel_send_work_queue send;
	/** Receive work queue */
	struct arbel_recv_work_queue recv;
};

/** Maximum number of allocatable completion queues
 *
 * This is a policy decision, not a device limit.
 */
#define ARBEL_MAX_CQS		8

/** An Arbel completion queue */
struct arbel_completion_queue {
	/** Consumer counter doorbell record number */
	unsigned int ci_doorbell_idx;
	/** Arm queue doorbell record number */
	unsigned int arm_doorbell_idx;
	/** Completion queue entries */
	union arbelprm_completion_entry *cqe;
	/** Size of completion queue */
	size_t cqe_size;
};

/** An Arbel resource bitmask */
typedef uint32_t arbel_bitmask_t;

/** Size of an Arbel resource bitmask */
#define ARBEL_BITMASK_SIZE(max_entries)					     \
	( ( (max_entries) + ( 8 * sizeof ( arbel_bitmask_t ) ) - 1 ) /	     \
	  ( 8 * sizeof ( arbel_bitmask_t ) ) )

/** An Arbel device */
struct arbel {
	/** PCI configuration registers */
	void *config;
	/** PCI user Access Region */
	void *uar;

	/** Command input mailbox */
	void *mailbox_in;
	/** Command output mailbox */
	void *mailbox_out;

	/** Firmware area in external memory */
	userptr_t firmware_area;
	/** ICM size */
	size_t icm_len;
	/** ICM AUX size */
	size_t icm_aux_len;
	/** ICM area */
	userptr_t icm;

	/** Doorbell records */
	union arbelprm_doorbell_record *db_rec;
	/** Reserved LKey
	 *
	 * Used to get unrestricted memory access.
	 */
	unsigned long reserved_lkey;

	/** Completion queue in-use bitmask */
	arbel_bitmask_t cq_inuse[ ARBEL_BITMASK_SIZE ( ARBEL_MAX_CQS ) ];
	/** Queue pair in-use bitmask */
	arbel_bitmask_t qp_inuse[ ARBEL_BITMASK_SIZE ( ARBEL_MAX_QPS ) ];
	
	/** Device limits */
	struct arbel_dev_limits limits;
};

/** Global protection domain */
#define ARBEL_GLOBAL_PD			0x123456

/** Memory key prefix */
#define ARBEL_MKEY_PREFIX		0x77000000UL

/*
 * HCA commands
 *
 */

#define ARBEL_HCR_BASE			0x80680
#define ARBEL_HCR_REG(x)		( ARBEL_HCR_BASE + 4 * (x) )
#define ARBEL_HCR_MAX_WAIT_MS		2000
#define ARBEL_MBOX_ALIGN		4096
#define ARBEL_MBOX_SIZE			512

/* HCA command is split into
 *
 * bits  11:0	Opcode
 * bit     12	Input uses mailbox
 * bit     13	Output uses mailbox
 * bits 22:14	Input parameter length (in dwords)
 * bits 31:23	Output parameter length (in dwords)
 *
 * Encoding the information in this way allows us to cut out several
 * parameters to the arbel_command() call.
 */
#define ARBEL_HCR_IN_MBOX		0x00001000UL
#define ARBEL_HCR_OUT_MBOX		0x00002000UL
#define ARBEL_HCR_OPCODE( _command )	( (_command) & 0xfff )
#define ARBEL_HCR_IN_LEN( _command )	( ( (_command) >> 12 ) & 0x7fc )
#define ARBEL_HCR_OUT_LEN( _command )	( ( (_command) >> 21 ) & 0x7fc )

/** Build HCR command from component parts */
#define ARBEL_HCR_INOUT_CMD( _opcode, _in_mbox, _in_len,		     \
			     _out_mbox, _out_len )			     \
	( (_opcode) |							     \
	  ( (_in_mbox) ? ARBEL_HCR_IN_MBOX : 0 ) |			     \
	  ( ( (_in_len) / 4 ) << 14 ) |					     \
	  ( (_out_mbox) ? ARBEL_HCR_OUT_MBOX : 0 ) |			     \
	  ( ( (_out_len) / 4 ) << 23 ) )

#define ARBEL_HCR_IN_CMD( _opcode, _in_mbox, _in_len )			     \
	ARBEL_HCR_INOUT_CMD ( _opcode, _in_mbox, _in_len, 0, 0 )

#define ARBEL_HCR_OUT_CMD( _opcode, _out_mbox, _out_len )		     \
	ARBEL_HCR_INOUT_CMD ( _opcode, 0, 0, _out_mbox, _out_len )

#define ARBEL_HCR_VOID_CMD( _opcode )					     \
	ARBEL_HCR_INOUT_CMD ( _opcode, 0, 0, 0, 0 )

/*
 * Doorbell record allocation
 *
 * The doorbell record map looks like:
 *
 *    ARBEL_MAX_CQS * Arm completion queue doorbell
 *    ARBEL_MAX_QPS * Send work request doorbell
 *    Group separator
 *    ...(empty space)...
 *    ARBEL_MAX_QPS * Receive work request doorbell
 *    ARBEL_MAX_CQS * Completion queue consumer counter update doorbell
 */

#define ARBEL_MAX_DOORBELL_RECORDS 512
#define ARBEL_GROUP_SEPARATOR_DOORBELL ( ARBEL_MAX_CQS + ARBEL_MAX_QPS )

/**
 * Get arm completion queue doorbell index
 *
 * @v cqn_offset	Completion queue number offset
 * @ret doorbell_idx	Doorbell index
 */
static inline unsigned int
arbel_cq_arm_doorbell_idx ( unsigned int cqn_offset ) {
	return cqn_offset;
}

/**
 * Get send work request doorbell index
 *
 * @v qpn_offset	Queue pair number offset
 * @ret doorbell_idx	Doorbell index
 */
static inline unsigned int
arbel_send_doorbell_idx ( unsigned int qpn_offset ) {
	return ( ARBEL_MAX_CQS + qpn_offset );
}

/**
 * Get receive work request doorbell index
 *
 * @v qpn_offset	Queue pair number offset
 * @ret doorbell_idx	Doorbell index
 */
static inline unsigned int
arbel_recv_doorbell_idx ( unsigned int qpn_offset ) {
	return ( ARBEL_MAX_DOORBELL_RECORDS - ARBEL_MAX_CQS - qpn_offset - 1 );
}

/**
 * Get completion queue consumer counter doorbell index
 *
 * @v cqn_offset	Completion queue number offset
 * @ret doorbell_idx	Doorbell index
 */
static inline unsigned int
arbel_cq_ci_doorbell_idx ( unsigned int cqn_offset ) {
	return ( ARBEL_MAX_DOORBELL_RECORDS - cqn_offset - 1 );
}

#endif /* _ARBEL_H */
