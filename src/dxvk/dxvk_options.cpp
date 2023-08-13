#include "dxvk_options.h"

namespace dxvk {

  DxvkOptions::DxvkOptions(const Config& config) {
    enableDebugUtils      = config.getOption<bool>    ("dxvk.enableDebugUtils",       false);
    enableStateCache      = config.getOption<bool>    ("dxvk.enableStateCache",       true);
    numCompilerThreads    = config.getOption<int32_t> ("dxvk.numCompilerThreads",     0);
    enableGraphicsPipelineLibrary = config.getOption<Tristate>("dxvk.enableGraphicsPipelineLibrary", Tristate::Auto);
    trackPipelineLifetime = config.getOption<Tristate>("dxvk.trackPipelineLifetime",  Tristate::Auto);
    useRawSsbo            = config.getOption<Tristate>("dxvk.useRawSsbo",             Tristate::Auto);
    maxChunkSize          = config.getOption<int32_t> ("dxvk.maxChunkSize",           0);
    hud                   = config.getOption<std::string>("dxvk.hud", "");

    if (env::getEnvVar("DXVK_GPLASYNCCACHE") == "1")
      gplAsyncCache = true;
    else
      gplAsyncCache = config.getOption<bool>("dxvk.gplAsyncCache", false);
    
    if (env::getEnvVar("DXVK_ASYNC") == "1")
      enableAsync = true;
    else
      enableAsync = config.getOption<bool>("dxvk.enableAsync", false);
  } 

}
