/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _ARRAYSUM_H_RPCGEN
#define _ARRAYSUM_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct mystruct {
	int n;
	int a1[100];
	int a2[100];
};
typedef struct mystruct mystruct;

#define ARRAYSUMPROG 0x23782fff
#define PROGVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define sum_function 1
extern  int * sum_function_1(mystruct *, CLIENT *);
extern  int * sum_function_1_svc(mystruct *, struct svc_req *);
extern int arraysumprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define sum_function 1
extern  int * sum_function_1();
extern  int * sum_function_1_svc();
extern int arraysumprog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_mystruct (XDR *, mystruct*);

#else /* K&R C */
extern bool_t xdr_mystruct ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_ARRAYSUM_H_RPCGEN */
