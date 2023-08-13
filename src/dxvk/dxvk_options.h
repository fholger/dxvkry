#pragma once

#include "../util/config/config.h"
#include "dxvk_include.h"

namespace dxvk {

  struct DxvkOptions {
    DxvkOptions() { }
    DxvkOptions(const Config& config);

    /// Enable debug utils
    bool enableDebugUtils;

    /// Enable state cache
    bool enableStateCache;

    /// Number of compiler threads
    /// when using the state cache
    int32_t numCompilerThreads;

    /// Enable graphics pipeline library
    Tristate enableGraphicsPipelineLibrary;

    /// Enables pipeline lifetime tracking
    Tristate trackPipelineLifetime;

    // Enable async pipelines
    bool enableAsync;
    // Enable state cache with gpl and fixes for async
    bool gplAsyncCache;

    /// Shader-related options
    Tristate useRawSsbo;

    /// Maximum memory chunk size in MiB
    int32_t maxChunkSize;

    /// HUD elements
    std::string hud;
  };

}
