/*
 * Copyright (c) 2020-2021, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *	* Redistributions of source code must retain the above copyright
 *	  notice, this list of conditions and the following disclaimer.
 *	* Redistributions in binary form must reproduce the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer in the documentation and/or other materials provided
 *	  with the distribution.
 *	* Neither the name of The Linux Foundation nor the names of its
 *	  contributors may be used to endorse or promote products derived
 *	  from this software without specific prior written permission.
 *
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <unordered_map>
#include <android-base/logging.h>
#include <android/hardware/thermal/2.0/IThermal.h>

#include "thermalData.h"
#include "thermalConfig.h"

namespace android {
namespace hardware {
namespace thermal {
namespace V2_0 {
namespace implementation {
	constexpr std::string_view socIDPath("/sys/devices/soc0/soc_id");

	std::vector<std::string> cpu_sensors_8917 =
	{
		"apc1-cpu0-usr",
		"apc1-cpu1-usr",
		"apc1-cpu2-usr",
		"apc1-cpu3-usr",
	};

	std::vector<struct target_therm_cfg> sensor_cfg_8917 =
	{
		{
			TemperatureType::CPU,
			cpu_sensors_8917,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpu0-usr" },
			"GPU",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "xo-therm-adc" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
	};

	std::vector<std::string> cpu_sensors_8937 =
	{
		"apc1-cpu0-usr",
		"apc1-cpu1-usr",
		"apc1-cpu2-usr",
		"apc1-cpu3-usr",
		"cpuss0-usr",
		"cpuss0-usr",
		"cpuss0-usr",
		"cpuss0-usr",
	};

	std::vector<struct target_therm_cfg> sensor_cfg_8937 =
	{
		{
			TemperatureType::CPU,
			cpu_sensors_8937,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpu-usr" },
			"GPU",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "xo-therm-adc" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
	};

	std::vector<std::string> cpu_sensors_8953 =
	{
		"apc1-cpu0-usr",
		"apc1-cpu1-usr",
		"apc1-cpu2-usr",
		"apc1-cpu3-usr",
		"apc0-cpu0-usr",
		"apc0-cpu1-usr",
		"apc0-cpu2-usr",
		"apc0-cpu3-usr",
	};

	std::vector<struct target_therm_cfg> sensor_cfg_8953 =
	{
		{
			TemperatureType::CPU,
			cpu_sensors_8953,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpu0-usr", "gpu1-usr" },
			"GPU",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "xo-therm-adc" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
	};

	std::vector<std::string> cpu_sensors_429 =
	{
		"apc1-cpu0-usr",
		"apc1-cpu1-usr",
		"apc1-cpu2-usr",
		"apc1-cpu3-usr",
		"cpuss0-usr",
		"cpuss0-usr",
		"cpuss0-usr",
		"cpuss0-usr",
	};

	std::vector<struct target_therm_cfg> sensor_cfg_429 =
	{
		{
			TemperatureType::CPU,
			cpu_sensors_429,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpu-usr" },
			"GPU",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "quiet-therm-adc" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
		{
			TemperatureType::BCL_VOLTAGE,
			{ "vbat_adc" },
			"vbat",
			3200,
			3000,
			3200,
			false,
		},
		{
			TemperatureType::BCL_CURRENT,
			{ "ibat-high" },
			"ibat",
			4200,
			4400,
			4200,
			true,
		},
		{
			TemperatureType::BCL_PERCENTAGE,
			{ "soc" },
			"soc",
			10,
			2,
			10,
			false,
		},
	};

	std::vector<std::string> cpu_sensors_439 =
	{
		"apc1-cpu0-usr",
		"apc1-cpu1-usr",
		"apc1-cpu2-usr",
		"apc1-cpu3-usr",
		"cpuss0-usr",
		"cpuss0-usr",
		"cpuss0-usr",
		"cpuss0-usr",
	};

	std::vector<struct target_therm_cfg> sensor_cfg_439 =
	{
		{
			TemperatureType::CPU,
			cpu_sensors_439,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpu-usr" },
			"GPU",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "quiet-therm-adc" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
/*
		{
			TemperatureType::BCL_VOLTAGE,
			{ "pmi-vbat-lvl0" },
			"vbat",
			3200,
			3000,
			3200,
			false,
		},
		{
			TemperatureType::BCL_CURRENT,
			{ "pmi-ibat-lvl0" },
			"ibat",
			4200,
			4400,
			4200,
			true,
		},
		{
			TemperatureType::BCL_PERCENTAGE,
			{ "soc" },
			"soc",
			10,
			2,
			10,
			false,
		},
*/
	};

	std::vector<std::string> cpu_sensors_632 =
	{
		"cpuss0-usr",
		"cpuss0-usr",
		"cpuss0-usr",
		"cpuss0-usr",
		"apc1-cpu0-usr",
		"apc1-cpu1-usr",
		"apc1-cpu2-usr",
		"apc1-cpu3-usr",
	};

	std::vector<struct target_therm_cfg> sensor_cfg_632 =
	{
		{
			TemperatureType::CPU,
			cpu_sensors_632,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpu0-usr" },
			"GPU",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "quiet-therm-adc" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
	};

	std::vector<std::string> cpu_sensors_monaco =
	{
		"cpuss-0-usr",
		"cpuss-1-usr",
		"cpuss-0-usr",
		"cpuss-1-usr",
	};

	std::vector<struct target_therm_cfg> sensor_cfg_monaco =
	{
		{
			TemperatureType::CPU,
			cpu_sensors_monaco,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpu-usr" },
			"gpu",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "quiet-therm-usr" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
		{
			TemperatureType::BCL_CURRENT,
			{ "pm5100-ibat-lvl0" },
			"ibat",
			1100,
			1500,
			1100,
			true,
		},
	};

	std::vector<std::string> cpu_sensors_sdm845 =
	{
		"cpu0-silver-usr",
		"cpu1-silver-usr",
		"cpu2-silver-usr",
		"cpu3-silver-usr",
		"cpu0-gold-usr",
		"cpu1-gold-usr",
		"cpu2-gold-usr",
		"cpu3-gold-usr",
	};

	std::vector<struct target_therm_cfg> sensor_cfg_sdm845 = {
		{
			TemperatureType::CPU,
			cpu_sensors_sdm845,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{"gpu0-usr"},
			"gpu0",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{"gpu1-usr"},
			"gpu1",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{"xo-therm-adc"},
			"skin",
			40000,
			95000,
			40000,
			true,
		},
		{
			TemperatureType::BCL_PERCENTAGE,
			{"soc"},
			"soc",
			10,
			2,
			10,
			false,
		},
	};

	std::vector<std::string> cpu_sensors_bengal =
	{
		"cpuss-2-usr",
		"cpuss-2-usr",
		"cpuss-2-usr",
		"cpuss-2-usr",
		"cpu-1-0-usr",
		"cpu-1-1-usr",
		"cpu-1-2-usr",
		"cpu-1-3-usr",
	};

	std::vector<struct target_therm_cfg> sensor_cfg_bengal =
	{
		{
			TemperatureType::CPU,
			cpu_sensors_bengal,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpu-usr" },
			"GPU",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "xo-therm-usr" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
		{
			TemperatureType::BCL_VOLTAGE,
			{ "pmi632-vbat-lvl0" },
			"vbat",
			3000,
			2800,
			3000,
			false,
		},
		{
			TemperatureType::BCL_CURRENT,
			{ "pmi632-ibat-lvl0" },
			"ibat",
			4000,
			4200,
			4000,
			true,
		},
		{
			TemperatureType::BCL_PERCENTAGE,
			{ "soc" },
			"soc",
			10,
			2,
			10,
			false,
		},
	};

	std::vector<struct target_therm_cfg> sensor_cfg_khaje =
	{
		{
			TemperatureType::CPU,
			cpu_sensors_bengal,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpu-usr" },
			"GPU",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "xo-therm-usr" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
		{
			TemperatureType::BCL_VOLTAGE,
			{ "pm7250b-vbat-lvl0" },
			"vbat",
			3000,
			2800,
			3000,
			false,
		},
		{
			TemperatureType::BCL_CURRENT,
			{ "pm7250b-ibat-lvl0" },
			"ibat",
			5500,
			6000,
			5500,
			true,
		},
		{
			TemperatureType::BCL_PERCENTAGE,
			{ "soc" },
			"soc",
			10,
			2,
			10,
			false,
		},
	};

	std::vector<std::string> cpu_sensors_trinket =
	{
		"cpuss-0-usr",
		"cpuss-0-usr",
		"cpuss-0-usr",
		"cpuss-0-usr",
		"cpu-1-0-usr",
		"cpu-1-1-usr",
		"cpu-1-2-usr",
		"cpu-1-3-usr",
	};

	std::vector<struct target_therm_cfg> sensor_cfg_trinket =
	{
		{
			TemperatureType::CPU,
			cpu_sensors_trinket,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpu-usr" },
			"GPU",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "xo-therm-adc" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
		{
			TemperatureType::BCL_VOLTAGE,
			{ "pmi632-vbat-lvl0" },
			"vbat",
			3000,
			2800,
			3000,
			false,
		},
		{
			TemperatureType::BCL_CURRENT,
			{ "pmi632-ibat-lvl0" },
			"ibat",
			4000,
			4200,
			4000,
			true,
		},
		{
			TemperatureType::BCL_PERCENTAGE,
			{ "soc" },
			"soc",
			10,
			2,
			10,
			false,
		},
	};

	std::vector<struct target_therm_cfg> sensor_cfg_sdm660 =
	{
		{
			TemperatureType::CPU,
			cpu_sensors_trinket,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpu-usr" },
			"GPU",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "xo-therm-adc" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
		{
			TemperatureType::BCL_VOLTAGE,
			{ "vbat_adc" },
			"vbat",
			3500,
			3300,
			3500,
			false,
		},
		{
			TemperatureType::BCL_CURRENT,
			{ "ibat-high" },
			"ibat",
			4200,
			4400,
			4200,
			true,
		},
		{
			TemperatureType::BCL_PERCENTAGE,
			{ "soc" },
			"soc",
			10,
			2,
			10,
			false,
		},
	};

	std::vector<std::string> cpu_sensors_lito =
	{
		"cpu-0-0-usr",
		"cpu-0-1-usr",
		"cpu-0-2-usr",
		"cpu-0-3-usr",
		"cpu-0-4-usr",
		"cpu-0-5-usr",
		"cpu-1-0-usr",
		"cpu-1-2-usr",
	};

	std::vector<struct target_therm_cfg> sensor_cfg_lito =
	{
		{
			TemperatureType::CPU,
			cpu_sensors_lito,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpuss-0-usr" },
			"GPU",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "xo-therm-usr" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
		{
			TemperatureType::BCL_CURRENT,
			{ "pm7250b-ibat-lvl0" },
			"ibat",
			4500,
			5000,
			4500,
			true,
		},
		{
			TemperatureType::BCL_VOLTAGE,
			{ "pm7250b-vbat-lvl0" },
			"vbat",
			3200,
			3000,
			3200,
			false,
		},
		{
			TemperatureType::BCL_PERCENTAGE,
			{ "soc" },
			"soc",
			10,
			2,
			10,
			false,
		},
	};

	std::vector<struct target_therm_cfg> sensor_cfg_sdmmagpie =
	{
		{
			TemperatureType::CPU,
			cpu_sensors_lito,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpuss-0-usr" },
			"GPU",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "xo-therm-adc" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
		{
			TemperatureType::BCL_VOLTAGE,
			{ "pm6150-vbat-lvl0" },
			"vbat",
			3000,
			2800,
			3000,
			false,
		},
		{
			TemperatureType::BCL_CURRENT,
			{ "pm6150-ibat-lvl0" },
			"ibat",
			5500,
			6000,
			5500,
			true,
		},
		{
			TemperatureType::BCL_PERCENTAGE,
			{ "soc" },
			"soc",
			10,
			2,
			10,
			false,
		},
	};

	std::vector<struct target_therm_cfg> sensor_cfg_holi =
	{
		{
			TemperatureType::CPU,
			cpu_sensors_lito,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpuss-0-usr" },
			"gpu0",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpuss-1-usr" },
			"gpu1",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "quiet-therm-usr" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
		{
			TemperatureType::BCL_CURRENT,
			{ "pm7250b-ibat-lvl0" },
			"ibat",
			5500,
			6000,
			5500,
			true,
		},
	};

	std::vector<std::string> cpu_sensors_kona =
	{
		"cpu-0-0-usr",
		"cpu-0-1-usr",
		"cpu-0-2-usr",
		"cpu-0-3-usr",
		"cpu-1-0-usr",
		"cpu-1-1-usr",
		"cpu-1-2-usr",
		"cpu-1-3-usr",
	};

	std::vector<struct target_therm_cfg>  sensor_cfg_msmnile = {
		{
			TemperatureType::CPU,
			cpu_sensors_kona,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpuss-0-usr" },
			"gpu0",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpuss-1-usr" },
			"gpu1",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "xo-therm" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
		{
			TemperatureType::BCL_CURRENT,
			{ "pm8150b-ibat-lvl0" },
			"ibat",
			4500,
			5000,
			4500,
			true,
		},
		{
			TemperatureType::BCL_VOLTAGE,
			{ "pm8150b-vbat-lvl0" },
			"vbat",
			3200,
			3000,
			3200,
			false,
		},
		{
			TemperatureType::BCL_PERCENTAGE,
			{ "soc" },
			"soc",
			10,
			2,
			10,
			false,
		},
	};

	std::vector<struct target_therm_cfg>  kona_common = {
		{
			TemperatureType::CPU,
			cpu_sensors_kona,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpuss-0-usr" },
			"GPU0",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpuss-1-usr" },
			"GPU1",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "skin-msm-therm-usr" },
			"skin",
			40000,
			95000,
			40000,
			true,
		}
	};

	std::vector<struct target_therm_cfg>  kona_specific = {
		{
			TemperatureType::BCL_CURRENT,
			{ "pm8150b-ibat-lvl0" },
			"ibat",
			4500,
			5000,
			4500,
			true,
		},
		{
			TemperatureType::BCL_VOLTAGE,
			{ "pm8150b-vbat-lvl0" },
			"vbat",
			3200,
			3000,
			3200,
			false,
		},
		{
			TemperatureType::BCL_PERCENTAGE,
			{ "soc" },
			"soc",
			10,
			2,
			10,
			false,
		},
		{
			TemperatureType::NPU,
			{ "npu-usr" },
			"npu",
			95000,
			115000,
			95000,
			true,
		},
	};

	std::vector<std::string> cpu_sensors_lahaina =
	{
		"cpu-0-0-usr",
		"cpu-0-1-usr",
		"cpu-0-2-usr",
		"cpu-0-3-usr",
		"cpu-1-0-usr",
		"cpu-1-2-usr",
		"cpu-1-4-usr",
		"cpu-1-6-usr",
	};

	std::vector<struct target_therm_cfg>  lahaina_common = {
		{
			TemperatureType::CPU,
			cpu_sensors_lahaina,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpuss-0-usr" },
			"GPU0",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpuss-1-usr" },
			"GPU1",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::BCL_CURRENT,
			{ "pm8350b-ibat-lvl0" },
			"ibat",
			6000,
			7500,
			6000,
			true,
		},
		{
			TemperatureType::NPU,
			{ "nspss-0-usr" },
			"nsp0",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::NPU,
			{ "nspss-1-usr" },
			"nsp1",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::NPU,
			{ "nspss-2-usr" },
			"nsp2",
			95000,
			115000,
			95000,
			true,
		},
	};

	std::vector<struct target_therm_cfg>  lahaina_specific = {
		{
			TemperatureType::SKIN,
			{ "xo-therm-usr" },
			"skin",
			55000,
			95000,
			55000,
			true,
		},
	};

	std::vector<struct target_therm_cfg>  shima_specific = {
		{
			TemperatureType::SKIN,
			{ "quiet-therm-usr" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
	};

	std::vector<struct target_therm_cfg>  sensor_cfg_yupik = {
		{
			TemperatureType::CPU,
			cpu_sensors_lahaina,
			"",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpuss-0-usr" },
			"GPU0",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::GPU,
			{ "gpuss-1-usr" },
			"GPU1",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::NPU,
			{ "nspss-0-usr" },
			"nsp0",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::NPU,
			{ "nspss-1-usr" },
			"nsp1",
			95000,
			115000,
			95000,
			true,
		},
		{
			TemperatureType::SKIN,
			{ "quiet-therm-usr" },
			"skin",
			40000,
			95000,
			40000,
			true,
		},
	};

	struct target_therm_cfg bat_conf = {
		TemperatureType::BATTERY,
		{ "battery" },
		"battery",
		80000,
		90000,
		80000,
		true,
	};

	const std::unordered_map<int, std::vector<struct target_therm_cfg>>
		msm_soc_map = {
		{303, sensor_cfg_8917},
		{307, sensor_cfg_8917},
		{308, sensor_cfg_8917},
		{309, sensor_cfg_8917},
		{386, sensor_cfg_8917}, // QM215
		{294, sensor_cfg_8937}, // MSM8937
		{295, sensor_cfg_8937}, // APQ8937
		{313, sensor_cfg_8937}, // MSM8940
		{293, sensor_cfg_8953},
		{304, sensor_cfg_8953},
		{338, sensor_cfg_8953},
		{351, sensor_cfg_8953},
		{353, sensor_cfg_439},
		{354, sensor_cfg_429},
		{363, sensor_cfg_429},
		{364, sensor_cfg_429},
		{416, sensor_cfg_429},
		{437, sensor_cfg_429},
		{349, sensor_cfg_632},
		{350, sensor_cfg_632},
		{321, sensor_cfg_sdm845},
		{341, sensor_cfg_sdm845},
		{417, sensor_cfg_bengal}, // bengal
		{420, sensor_cfg_bengal},
		{444, sensor_cfg_bengal},
		{445, sensor_cfg_bengal},
		{469, sensor_cfg_bengal},
		{470, sensor_cfg_bengal},
		{518, sensor_cfg_khaje},  //khaje
		{394, sensor_cfg_trinket},
		{467, sensor_cfg_trinket},
		{468, sensor_cfg_trinket},
		{400, sensor_cfg_lito}, // lito
		{440, sensor_cfg_lito},
		{407, sensor_cfg_lito}, // atoll
		{317, sensor_cfg_sdm660},
		{345, sensor_cfg_sdm660}, // sdm636
		{365, sensor_cfg_sdmmagpie},
		{366, sensor_cfg_sdmmagpie},
		{434, sensor_cfg_lito}, // lagoon
		{435, sensor_cfg_lito},
		{459, sensor_cfg_lito},
		{476, sensor_cfg_lito}, // orchid
		{339, sensor_cfg_msmnile},
		{361, sensor_cfg_msmnile},
		{362, sensor_cfg_msmnile},
		{367, sensor_cfg_msmnile},
		{356, kona_common}, // kona
		{415, lahaina_common}, // lahaina
		{439, lahaina_common}, // lahainap
		{456, lahaina_common}, // lahaina-atp
		{501, lahaina_common},
		{502, lahaina_common},
		{450, lahaina_common}, // shima
		{454, sensor_cfg_holi}, // holi
		{507, sensor_cfg_holi}, // blair
		{475, sensor_cfg_yupik}, // yupik
		{515, sensor_cfg_yupik}, // YUPIK-LTE
		{486, sensor_cfg_monaco}, // monaco
	};

	const std::unordered_map<int, std::vector<struct target_therm_cfg>>
		msm_soc_specific = {
		{356, kona_specific}, // kona
		{415, lahaina_specific}, // lahaina
		{439, lahaina_specific}, // lahainap
		{456, lahaina_specific}, // lahaina-atp
		{501, lahaina_specific},
		{502, lahaina_specific},
		{450, shima_specific}, // shima
	};

	std::vector<struct target_therm_cfg> add_target_config(
			int socID,
			std::vector<struct target_therm_cfg> conf)
	{
		std::vector<struct target_therm_cfg> targetConf;

		if (msm_soc_specific.find(socID) == msm_soc_specific.end())
			return conf;
		targetConf = (msm_soc_specific.find(socID))->second;

		conf.insert(conf.end(), targetConf.begin(),
					targetConf.end());
		return conf;
	}

	ThermalConfig::ThermalConfig():cmnInst()
	{
		std::unordered_map<int, std::vector<struct target_therm_cfg>>::const_iterator it;
		std::vector<struct target_therm_cfg>::iterator it_vec;
		std::string soc_val;

		if (cmnInst.readFromFile(socIDPath, soc_val) <= 0) {
			LOG(ERROR) <<"soc ID fetch error";
			return;
		}
		soc_id = std::stoi(soc_val, nullptr, 0);
		if (soc_id <= 0) {
			LOG(ERROR) << "Invalid soc ID: " << soc_id;
			return;
		}
		it = msm_soc_map.find(soc_id);
		if (it == msm_soc_map.end()) {
			LOG(ERROR) << "No config for soc ID: " << soc_id;
			return;
		}
		thermalConfig = add_target_config(soc_id, it->second);

		thermalConfig.push_back(bat_conf);
		LOG(DEBUG) << "Total sensors:" << thermalConfig.size();
	}
}  // namespace implementation
}  // namespace V2_0
}  // namespace thermal
}  // namespace hardware
}  // namespace android

