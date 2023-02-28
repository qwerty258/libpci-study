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

    printf("DBDF, Vendor ID, Device ID, Class ID, Base Address 0, Size 0, Base Address 1, Size 1, Base Address 2, Size 2, Vendor, Device, Class\n");
    for (dev = pacc->devices; dev; dev = dev->next)
    {
        pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS |PCI_FILL_PHYS_SLOT);

        printf(
            "%04x:%02x:%02x.%d,"    // DBDF
            "0x%04X,"               // Vendor ID
            "0x%04X,"               // Device ID
            "0x%04X,"               // Class ID, 
            "0x%016X,"              // Base Address 0, 
            "0x%08X,"               // Size 0, 
            "0x%016X,"              // Base Address 1, 
            "0x%08X,"               // Size 1, 
            "0x%016X,"              // Base Address 2, 
            "0x%08X,",              // Size 2, 
            dev->domain, dev->bus, dev->dev, dev->func,
            dev->vendor_id,
            dev->device_id,
            dev->device_class,
            dev->base_addr[0], dev->size[0],
            dev->base_addr[1], dev->size[1],
            dev->base_addr[2], dev->size[2]);

        // Vendor, 
        name= pci_lookup_name(pacc, namebuf, sizeof(namebuf), PCI_LOOKUP_VENDOR, dev->vendor_id, dev->device_id);
        printf("%s,", name);
        // Device, 
        name = pci_lookup_name(pacc, namebuf, sizeof(namebuf), PCI_LOOKUP_DEVICE, dev->vendor_id, dev->device_id);
        printf("%s,", name);
        // Class
        name=pci_lookup_name(pacc, namebuf, sizeof(namebuf), PCI_LOOKUP_CLASS, dev->device_class);
        printf("%s", name);
        printf("\n", name);
    }
    pci_cleanup(pacc);		/* Close everything */
    return 0;
}
