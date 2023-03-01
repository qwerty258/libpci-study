#include <stdio.h>
#include <pci/pci.h>

int main()
{
    struct pci_access* pacc;
    struct pci_dev* dev;
    unsigned int c;
    char namebuf[1024], * name;

    pacc = pci_alloc();

    pci_init(pacc);
    pci_scan_bus(pacc);

    printf("[\n");
    for (dev = pacc->devices; NULL != dev; dev = dev->next)
    {
        pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS | PCI_FILL_PHYS_SLOT);

        printf("{");
        printf("\"DBDF\":\"%04x:%02x:%02x.%d\",", dev->domain, dev->bus, dev->dev, dev->func);
        printf("\"Vendor ID\":\"0x%04X\",", dev->vendor_id);
        printf("\"Device ID\":\"0x%04X\",", dev->device_id);
        printf("\"Class ID\":\"0x%04X\",", dev->device_class);
        printf("\"Base Address 0\":\"0x%016X\",\"Size 0\":\"0x%08X\",", dev->base_addr[0], dev->size[0]);
        printf("\"Base Address 1\":\"0x%016X\",\"Size 1\":\"0x%08X\",", dev->base_addr[1], dev->size[1]);
        printf("\"Base Address 2\":\"0x%016X\",\"Size 2\":\"0x%08X\",", dev->base_addr[2], dev->size[2]);

        name = pci_lookup_name(pacc, namebuf, sizeof(namebuf), PCI_LOOKUP_VENDOR, dev->vendor_id, dev->device_id);
        printf("\"Vendor\":\"%s\",", name);
        name = pci_lookup_name(pacc, namebuf, sizeof(namebuf), PCI_LOOKUP_DEVICE, dev->vendor_id, dev->device_id);
        printf("\"Device\":\"%s\",", name);
        name = pci_lookup_name(pacc, namebuf, sizeof(namebuf), PCI_LOOKUP_CLASS, dev->device_class);
        printf("\"Class\":\"%s\"", name);

        if (NULL == dev->next)
            printf("}\n");
        else
            printf("},\n");
    }
    printf("]\n");
    pci_cleanup(pacc);
    return 0;
}
