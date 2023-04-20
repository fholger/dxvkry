#include <d3d9_include.h>
#include <d3d9_interfaces.h>
#include <openvr/openvr.hpp>

extern "C" DLLEXPORT void dxvkLockSubmissionQueue(IDirect3DDevice9Ex *device, bool flush)
{
	dxvk::Com<ID3D9VkInteropDevice> vkDevice;
	device->QueryInterface(__uuidof(ID3D9VkInteropDevice), (void**) &vkDevice);
	if (flush)
		vkDevice->FlushRenderingCommands();
	vkDevice->LockSubmissionQueue();
}

extern "C" DLLEXPORT void dxvkReleaseSubmissionQueue(IDirect3DDevice9Ex *device)
{
	dxvk::Com<ID3D9VkInteropDevice> vkDevice;
	device->QueryInterface(__uuidof(ID3D9VkInteropDevice), (void**) &vkDevice);
	vkDevice->ReleaseSubmissionQueue();
}

extern "C" DLLEXPORT HRESULT dxvkFillVulkanTextureInfo(IDirect3DDevice9Ex *device, IDirect3DTexture9 *texture, vr::VRVulkanTextureData_t &data, VkImageLayout &layout)
{
	dxvk::Com<ID3D9VkInteropDevice> vkDevice;
	device->QueryInterface(__uuidof(ID3D9VkInteropDevice), (void**) &vkDevice);
	dxvk::Com<ID3D9VkInteropTexture> vkTex;
	texture->QueryInterface(__uuidof(ID3D9VkInteropTexture), (void**)&vkTex);
	VkImage image;
	VkImageCreateInfo createInfo {};
	createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	HRESULT hr = vkTex->GetVulkanImageInfo(&image, &layout, &createInfo);
	if (hr != S_OK)
	{
		return hr;
	}

	data.m_nFormat = createInfo.format;
	data.m_nWidth = createInfo.extent.width;
	data.m_nHeight = createInfo.extent.height;
	data.m_nImage = (uint64_t)image;
	data.m_nSampleCount = 1;
	vkDevice->GetSubmissionQueue(&data.m_pQueue, nullptr, &data.m_nQueueFamilyIndex);
	vkDevice->GetVulkanHandles(&data.m_pInstance, &data.m_pPhysicalDevice, &data.m_pDevice);

	return S_OK;
}

extern "C" DLLEXPORT void dxvkTransitionImageLayout(IDirect3DDevice9Ex *device, IDirect3DTexture9 *texture, VkImageLayout from, VkImageLayout to)
{
	dxvk::Com<ID3D9VkInteropDevice> vkDevice;
	device->QueryInterface(__uuidof(ID3D9VkInteropDevice), (void**) &vkDevice);
	dxvk::Com<ID3D9VkInteropTexture> vkTex;
	texture->QueryInterface(__uuidof(ID3D9VkInteropTexture), (void**)&vkTex);

	VkImageSubresourceRange range;
	range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	range.baseMipLevel = 0;
	range.levelCount = 1;
	range.baseArrayLayer = 0;
	range.layerCount = 1;
	vkDevice->TransitionTextureLayout(vkTex.ptr(), &range, from, to);
}
