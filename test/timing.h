/*
 *  timing.h
 *
 *  (C) René J.V. Bertin on 20080926.
 *
 */

#ifdef __cplusplus
extern "C"
{
#endif

extern void init_HRTime();
extern double HRTime_Time();
extern double HRTime_tic();
extern double HRTime_toc();

#ifdef __cplusplus
}
#endif
