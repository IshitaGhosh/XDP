/**
 * Copyright (C) 2022-2026 Advanced Micro Devices, Inc. - All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You may
 * not use this file except in compliance with the License. A copy of the
 * License is located at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#define XDP_PLUGIN_SOURCE

#include "aie_trace_cb.h"
#include "aie_trace_plugin.h"


namespace xdp {

  // AIE Trace Plugin has only a static instance of the plugin object and a callback

  static AieTracePluginUnified aieTracePluginInstance;

  static void updateAIEDevice(void* handle, bool hw_context_flow)
  {
    if (AieTracePluginUnified::alive())
      aieTracePluginInstance.updateAIEDevice(handle, hw_context_flow);
  }

  static void flushAIEDevice(void* handle)
  {
    if (AieTracePluginUnified::alive())
      aieTracePluginInstance.flushAIEDevice(handle);
  }

  static void finishFlushAIEDevice(void* handle)
  {
    if (AieTracePluginUnified::alive())
      aieTracePluginInstance.finishFlushAIEDevice(handle);
  }

  static void aieTraceRunConstructor(void* run_impl_ptr, void* hwctx, uint32_t run_uid,
                                      const char* kernel_name, void* elf_handle)
  {
    if (AieTracePluginUnified::alive())
      aieTracePluginInstance.runConstructorHook(run_impl_ptr, hwctx, run_uid,
                                                kernel_name ? kernel_name : "",
                                                elf_handle);
  }

  static void aieTraceRunStart(void* run_impl_ptr, void* hwctx, uint32_t run_uid, const char* kernel_name)
  {
    if (AieTracePluginUnified::alive())
      aieTracePluginInstance.runStartHook(run_impl_ptr, hwctx, run_uid,
                                          kernel_name ? kernel_name : "");
  }

  static void aieTraceRunWait(void* run_impl_ptr, void* hwctx, uint32_t run_uid, const char* kernel_name,
                              int ert_cmd_state)
  {
    if (AieTracePluginUnified::alive())
      aieTracePluginInstance.runWaitHook(run_impl_ptr, hwctx, run_uid,
                                         kernel_name ? kernel_name : "", ert_cmd_state);
  }
  
} // end namespace xdp

extern "C" 
void updateAIEDevice(void* handle, bool hw_context_flow)
{
  xdp::updateAIEDevice(handle, hw_context_flow);
}

extern "C" 
void flushAIEDevice(void* handle)
{
  xdp::flushAIEDevice(handle);
}

extern "C"
void finishFlushAIEDevice(void* handle)
{
  xdp::finishFlushAIEDevice(handle);
}

extern "C"
void aieTraceRunConstructor(void* run_impl_ptr, void* hwctx, uint32_t run_uid,
                            const char* kernel_name, void* elf_handle)
{
  xdp::aieTraceRunConstructor(run_impl_ptr, hwctx, run_uid, kernel_name, elf_handle);
}

extern "C"
void aieTraceRunStart(void* run_impl_ptr, void* hwctx, uint32_t run_uid, const char* kernel_name)
{
  xdp::aieTraceRunStart(run_impl_ptr, hwctx, run_uid, kernel_name);
}

extern "C"
void aieTraceRunWait(void* run_impl_ptr, void* hwctx, uint32_t run_uid, const char* kernel_name,
                     int ert_cmd_state)
{
  xdp::aieTraceRunWait(run_impl_ptr, hwctx, run_uid, kernel_name, ert_cmd_state);
}
