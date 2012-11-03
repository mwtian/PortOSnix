#ifndef __MINISOCKETS_PRIVATE_H_
#define __MINISOCKETS_PRIVATE_H_

#include "network.h"
#include "queue.h"
#include "synch.h"

#define MINISOCKET_MAX_MSG_SIZE (MAX_NETWORK_PKT_SIZE - MINISOCKET_HDRSIZE)
#define MINISOCKET_MIN_SERVER 0
#define MINISOCKET_MAX_SERVER 32767
#define MINISOCKET_MIN_CLIENT 32768
#define MINISOCKET_MAX_CLIENT 65535
#define MINISOCKET_PORT_NUM (MINISOCKET_MAX_CLIENT - MINISOCKET_MIN_SERVER + 1)
#define MINISOCKET_CLIENT_NUM (MINISOCKET_MAX_CLIENT - MINISOCKET_MIN_CLIENT + 1)
#define MINISOCKET_MAX_TRY 7
#define MINISOCKET_INITIAL_TIMEOUT 100
#define MINISOCKET_FIN_TIMEOUT 15000

struct minisocket
{
    int local_port_num;
	int remote_port_num;
    network_address_t remote_addr;
	network_address_t local_addr;
    int seq;
    int ack;
    int alarm;
	int receive_count;
    queue_t data;
    semaphore_t send_mutex; /* send mutex: only one thread can send */
    semaphore_t data_mutex; /* data queue */
    semaphore_t state_mutex; /* socket state */
    semaphore_t seq_mutex;   /* sequence number mutex */
	seamphore_t receive_count_mutex; /* receive count mutex */
    semaphore_t synchonize;
    semaphore_t retry;
    semaphore_t receive;
    enum socket_state {
		LISTEN,
		SYNSENT,
		SYNRECEIVED,
		ESTABLISHED,
		FINSENT,
		FINRECEIVED,
		CLOSEWAIT,
		LASTACK,
		CLOSED,
		FINWAIT1,
		FINWAIT2,
		CLOSING,
		TIMEWAIT
    } state;
};

typedef enum minisocket_interrupt_status {
    INTERRUPT_PROCESSED,
    INTERRUPT_STORED
} minisocket_interrupt_status;

#endif /* __MINISOCKETS_PRIVATE_H_ */
