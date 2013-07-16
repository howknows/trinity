/*
 * SYSCALL_DEFINE5(setsockopt, int, fd, int, level, int, optname, char __user *, optval, int, optlen)
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <bits/socket.h>
#include <netinet/in.h>
#include <linux/tcp.h>
#include <netinet/udp.h>
#include <netipx/ipx.h>
#include <netatalk/at.h>
#include <netax25/ax25.h>
#include <linux/icmpv6.h>
#include <linux/icmp.h>
#include <linux/if_packet.h>
#include <linux/if.h>
#include <linux/if_pppol2tp.h>

#include "compat.h"
#include "config.h"
#include "trinity.h"

#ifdef USE_CAIF
#include <linux/caif/caif_socket.h>
#endif

#ifdef USE_RDS
#include <linux/rds.h>
#endif

#define SOL_PPPOL2TP    273
#define SOL_BLUETOOTH   274
#define SOL_PNPIPE      275
#define SOL_RDS         276
#define SOL_IUCV        277
#define SOL_CAIF        278
#define SOL_ALG         279
#define SOL_NFC		280

#define NR_SOL_PPPOL2TP_OPTS ARRAY_SIZE(pppol2tp_opts)
static int pppol2tp_opts[] = {
	PPPOL2TP_SO_DEBUG, PPPOL2TP_SO_RECVSEQ, PPPOL2TP_SO_SENDSEQ, PPPOL2TP_SO_LNSMODE,
	PPPOL2TP_SO_REORDERTO };

#define NR_SOL_BLUETOOTH_OPTS ARRAY_SIZE(bluetooth_opts)
static int bluetooth_opts[] = {
	BT_SECURITY, BT_DEFER_SETUP, BT_FLUSHABLE, BT_POWER,
	BT_CHANNEL_POLICY };

#define NR_SOL_BLUETOOTH_HCI_OPTS ARRAY_SIZE(bluetooth_hci_opts)
static int bluetooth_hci_opts[] = {
	HCI_DATA_DIR, HCI_FILTER, HCI_TIME_STAMP };

#define NR_SOL_BLUETOOTH_L2CAP_OPTS ARRAY_SIZE(bluetooth_l2cap_opts)
static int bluetooth_l2cap_opts[] = {
	L2CAP_OPTIONS, L2CAP_LM };

#define NR_SOL_BLUETOOTH_RFCOMM_OPTS ARRAY_SIZE(bluetooth_rfcomm_opts)
static int bluetooth_rfcomm_opts[] = { RFCOMM_LM };

#ifdef USE_RDS
#define NR_SOL_RDS_OPTS ARRAY_SIZE(rds_opts)
static int rds_opts[] = {
	RDS_CANCEL_SENT_TO, RDS_GET_MR, RDS_FREE_MR,
	4, /* deprecated RDS_BARRIER 4 */
	RDS_RECVERR, RDS_CONG_MONITOR, RDS_GET_MR_FOR_DEST };
#endif

#define NR_SOL_IUCV_OPTS ARRAY_SIZE(iucv_opts)
static int iucv_opts[] = {
	SO_IPRMDATA_MSG, SO_MSGLIMIT, SO_MSGSIZE };

#ifdef USE_CAIF
#define NR_SOL_CAIF_OPTS ARRAY_SIZE(caif_opts)
static int caif_opts[] = {
	CAIFSO_LINK_SELECT, CAIFSO_REQ_PARAM };
#endif
