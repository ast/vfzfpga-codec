/*
 * Driver for the VFZFPGA codec
 *
 * Author:	Albin Stigo <albin.stigo@gmail.com>
 *
 * Author:	Florian Meier <florian.meier@koalo.de>
 *		Copyright 2013
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#include <sound/soc.h>

static struct snd_soc_dai_driver vfzfpga_dai = {
	.name = "vfzfpga-dai",
	.playback = {
        .stream_name = "playback",
		.channels_min = 2,
		.channels_max = 2,
        .rates = SNDRV_PCM_RATE_KNOT,
        .rate_min =	39000,
        .rate_max =	39000,
		.formats = SNDRV_PCM_FMTBIT_S16_LE |
			   SNDRV_PCM_FMTBIT_S24_LE |
			   SNDRV_PCM_FMTBIT_S32_LE
	},
    .capture = {
        .stream_name = "capture",
        .channels_min = 2,
        .channels_max = 2,
        .rates = SNDRV_PCM_RATE_KNOT,
        .rate_min =	39000,
        .rate_max =	39000,
        .formats = SNDRV_PCM_FMTBIT_S16_LE |
        SNDRV_PCM_FMTBIT_S24_LE |
        SNDRV_PCM_FMTBIT_S32_LE
    },
    .symmetric_rates = 1,
};

static struct snd_soc_codec_driver soc_codec_dev_vfzfpga;

static int vfzfpga_probe(struct platform_device *pdev)
{
    int ret = 0;
    
    ret = snd_soc_register_codec(&pdev->dev, &soc_codec_dev_vfzfpga,
                                 &vfzfpga_dai, 1);
    
    printk(KERN_ERR "return code: %d\n",ret);
    
    return ret;
}

static int vfzfpga_remove(struct platform_device *pdev)
{
	snd_soc_unregister_codec(&pdev->dev);
	return 0;
}

static const struct of_device_id vfzfpga_of_match[] = {
	{ .compatible = "altera,vfzfpga", },
	{ }
};
MODULE_DEVICE_TABLE(of, vfzfpga_of_match);

static struct platform_driver vfzfpga_codec_driver = {
	.probe		= vfzfpga_probe,
	.remove		= vfzfpga_remove,
	.driver		= {
		.name	= "vfzfpga",
        .owner = THIS_MODULE,
		.of_match_table = vfzfpga_of_match,
	},
};

module_platform_driver(vfzfpga_codec_driver);

MODULE_DESCRIPTION("ASoC VFZFPGA codec driver");
MODULE_AUTHOR("Albin Stigo <albin.stigo@gmail.com>");
MODULE_LICENSE("GPL v2");
