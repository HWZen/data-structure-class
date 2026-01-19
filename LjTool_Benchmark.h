// copyright 2024 The Master ZZ C++_Group Authors. All rights reserved.
// author huangqiang01@zhuanzhuan.com
// date 2024/06/16 12:27:30

#ifndef LJTOOL_FRONT_LJTOOLS_RUNBENCH_H
#define LJTOOL_FRONT_LJTOOLS_RUNBENCH_H

#if defined(LJTOOL_FRONT_LIBRARY)
#  define LJTOOL_FRONT_EXPORT __declspec(dllexport)
#else
#  define LJTOOL_FRONT_EXPORT __declspec(dllimport)
#endif // LJTOOL_FRONT_LIBRARY

#ifdef __cplusplus
extern "C" {
#endif

    enum RunBenchType {
        RunBenchCpu = 1,  // CPU跑分
        RunBenchGpu = 2,  // GPU跑分
        RunBenchGpuNoUI = 4,  // 无UI的GPU跑分
        RunBenchMem = 8,  // 内存跑分
        RunBenchDisk = 16,  // 磁盘跑分
      };

    //支持评测class的id
    enum ClassID {
        kBegin = -1,
        kAll = 0,
        kCpu,  // CPU id
        kGpu,
        kMem,
        kDisk,
        kEnd = 50
      };

    enum OpType {
        OpOnStart = 1, // 本次评测开始
        OpOnClassStart, // 本次评测中的单项开始
        OpOnClassEnd, // 本次评测中的单项结束
        OpOnEnd, // 本次评测结束，回调结果
      };


    /*
    * @brief: 初始化跑分程序，跑分前的初始化操作
    */
    LJTOOL_FRONT_EXPORT void InitRunBench();

    /*
     * @brief: 开始运行笔记本跑分
     * @param: type 跑分类型，参考 RunBenchType 的按位或组合
     *         runbench_callback 回调函数，跑分大项及其子项进度，及最后跑分结果
     */
    LJTOOL_FRONT_EXPORT void StartRunBench(void(*runbench_callback)(const char*), int type);

    /*
     * @brief: 取消跑分，可能会有几s延迟，取消也会有结果回调
     * @param: class_id 跑分项，参考 ClassID
     */
    LJTOOL_FRONT_EXPORT void CancelRunBench(int class_id);

    /*
  * @brief: 跑分程序的反初始化
  */
    LJTOOL_FRONT_EXPORT void UnInitRunBench();

    /*
  * @brief: 获取3D跑分FPS
  */
    LJTOOL_FRONT_EXPORT float Get3DBenchFps();

    /*
   * @brief: 高性能调整，返回值表示是否设置成功
   * @param: enable 1 设置高性能， 0 恢复用户默认设置
   */
    LJTOOL_FRONT_EXPORT bool SetHighPerf(int enable);

#ifdef __cplusplus
}
#endif

#endif //LJTOOL_FRONT_LJTOOLS_RUNBENCH_H

