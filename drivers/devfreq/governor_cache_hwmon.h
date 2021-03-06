/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _GOVERNOR_CACHE_HWMON_H
#define _GOVERNOR_CACHE_HWMON_H

#include <linux/kernel.h>
#include <linux/devfreq.h>

struct mrps_stats {
	unsigned long high;
	unsigned long med;
	unsigned long low;
	unsigned int busy_percent;
};

/**
 * struct cache_hwmon - devfreq Cache HW monitor info
 * @start_hwmon:	Start the HW monitoring
 * @stop_hwmon:		Stop the HW monitoring
 * @is_valid_irq:	Check whether the IRQ was triggered by the counter
 *			used to monitor cache activity.
 * @meas_mrps_and_set_irq:	Return the measured count and set up the
 *				IRQ to fire if usage exceeds current
 *				measurement by @tol percent.
 * @irq:		IRQ number that corresponds to this HW monitor.
 * @dev:		device that this HW monitor can monitor.
 * @of_node:		OF node of device that this HW monitor can monitor.
 * @df:			Devfreq node that this HW montior is being used
 *			for. NULL when not actively in use, and non-NULL
 *			when in use.
 */
struct cache_hwmon {
	int (*start_hwmon)(struct cache_hwmon *hw, struct mrps_stats *mrps);
	void (*stop_hwmon)(struct cache_hwmon *hw);
	bool (*is_valid_irq)(struct cache_hwmon *hw);
	unsigned long (*meas_mrps_and_set_irq)(struct cache_hwmon *hw,
					unsigned int tol, unsigned int us,
					struct mrps_stats *mrps);
	int irq;
	struct device *dev;
	struct device_node *of_node;
	struct devfreq *df;
};

#ifdef CONFIG_DEVFREQ_GOV_MSM_CACHE_HWMON
int register_cache_hwmon(struct device *dev, struct cache_hwmon *hwmon);
#else
static inline int register_cache_hwmon(struct device *dev,
				       struct cache_hwmon *hwmon)
{
	return 0;
}
#endif

#endif /* _GOVERNOR_CACHE_HWMON_H */
