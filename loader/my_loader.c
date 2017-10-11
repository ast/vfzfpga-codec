#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kmod.h>
#include <linux/platform_device.h>
#include <sound/simple_card.h>
#include <linux/delay.h>


void device_release_callback(struct device *dev) { /*  do nothing */ };

static struct asoc_simple_card_info snd_rpi_simple_card_info = {
    .name = "simple-card_codec_link", // -> snd_soc_dai_link.name
    .card = "snd_rpi_simple_card", // -> snd_soc_card.name
    .codec = "snd-soc-dummy", // "snd-soc-dummy", // "dmic-codec", // -> snd_soc_dai_link.codec_name
    .platform = "3f203000.i2s",
    .daifmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBM_CFM,
    .cpu_dai = {
        .name = "3f203000.i2s", // -> snd_soc_dai_link.cpu_dai_name
        .sysclk = 0 },
    .codec_dai = {
        .name = "snd-soc-dummy-dai", //"snd-soc-dummy-dai", //"dmic-codec", // -> snd_soc_dai_link.codec_dai_name
        .sysclk = 0 },
};

static struct platform_device snd_rpi_simple_card_device = {
    .name = "asoc-simple-card", //module alias
    .id = 0,
    .num_resources = 0,
    .dev = { .release = &device_release_callback,
        .platform_data = &snd_rpi_simple_card_info, // *HACK ALERT*
    },
};


int hello_init(void)
{
    const char *dmaengine = "bcm2708-dmaengine"; //module name
    int ret;
    
    ret = request_module(dmaengine);
    pr_alert("request module load '%s': %d\n",dmaengine, ret);
    ret = platform_device_register(&snd_rpi_simple_card_device);
    pr_alert("register platform device '%s': %d\n",snd_rpi_simple_card_device.name, ret);
    
    pr_alert("Hello World :)\n");
    return 0;
}

void hello_exit(void)
{// you'll have to sudo modprobe -r the card & codec drivers manually (first?)
    platform_device_unregister(&snd_rpi_simple_card_device);
    pr_alert("Goodbye World!\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_DESCRIPTION("ASoC simple-card I2S setup");
MODULE_AUTHOR("Plugh Plover");
MODULE_LICENSE("GPL v2");

