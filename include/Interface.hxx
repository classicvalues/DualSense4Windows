#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <map>
#include <memory>
#include <ViGEm/Client.h>

#include "Types.hxx"

namespace BrokenBytes::DualSense4Windows {
	class DualSense;
	struct DS_REPORT;
}

namespace BrokenBytes::DualSense4Windows {
	// Hardware IDs
	constexpr uint16_t SONY = 0x054C;
	constexpr uint16_t DS = 0x0CE6;
	constexpr int8_t DS_INTERFACE = 0x03;

	class Interface {
	public:
		/// <summary>
		/// Creates the Interface singleton
		/// </summary>
		/// <returns>The singleton</returns>
		[[nodiscard]] static std::shared_ptr<Interface> Create();
		
		/// <summary>
		/// Inits the Interface
		/// </summary>
		void Init();
		
		/// <summary>
		/// Gets all DualSense devices connected
		/// </summary>
		/// <returns>A map of devices, by HID path and instance </returns>
		std::map<char*, DualSense*> GetDualSenses();
		/// <summary>
		/// Updates the list of connected DualSenses
		/// </summary>
		void UpdateDualSenseDevices();

		/// <summary>
		/// Creates a new virtual device with type
		/// </summary>
		/// <param name="mode"></param>
		/// <returns>The virtual device</returns>
		PVIGEM_TARGET CreateVirtualDevice(ControllerMode mode);

		/// <summary>
		/// Removes a virtual device from the bus
		/// </summary>
		/// <param name="">The device to remove</param>
		void RemoveVirtualDevice(PVIGEM_TARGET device);

		/// <summary>
		/// Binds a virtual device to a physical DualSense
		/// </summary>
		/// <param name="device">The device to bind</param>
		/// <param name="target">The target to be bound to</param>
		void BindVirtualDevice(DualSense* device, PVIGEM_TARGET target);

	private:
		static inline  std::weak_ptr<Interface> _interface;
		PVIGEM_CLIENT _client;
		std::map<char*, DualSense*> _devices;
		std::map<char*, PVIGEM_TARGET> _virtualDevices;

		// Private to enforce singleton
		Interface();
		void InitViGEmClient();
	};
}