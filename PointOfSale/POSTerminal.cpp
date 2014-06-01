#include <POSTerminal.h>
#include <string.h>

POSTerminal::POSTerminal()
{
	memset(d_itemCounts, 0, sizeof(d_itemCounts));
	memset(d_pricingTable, 0, sizeof(d_pricingTable));
}

POSTerminal::~POSTerminal()
{
}

void POSTerminal::setPrice(char item, double unitPrice,
				int volumeQty, double volumePrice)
{
	d_pricingTable[item].d_unitPrice=unitPrice;
	d_pricingTable[item].d_volumeQty=volumeQty;
	d_pricingTable[item].d_volumePrice=volumePrice;

	//@IMPROVE - do the following checks 
	//(1) unitPrice is non-zero
    //(2) unitPrice and volumePrice consistency?
}

void POSTerminal::scanItem(char item)
{
	d_itemCounts[item]++;
}

void POSTerminal::scanMultipleItems(const char *items)
{
    for(int i=0; i<strlen(items); ++i)
    {
        scanItem(items[i]);
    }
}

double POSTerminal::getTotal() const
{
	double runningTotal=0.0;

	for (int i=0; i < sizeof(d_itemCounts) / sizeof(int); ++i)
	{
		if((d_itemCounts[i] > 0) &&
				(d_pricingTable[i].d_unitPrice > 0.0))
		{
			//@IMPROVE - flag errros for items without pricing

			runningTotal+=getSingleItemTotal(d_itemCounts[i],
					d_pricingTable[i]);
		}   		
	}

	return runningTotal;
}

double POSTerminal::getSingleItemTotal(int count, 
				const ItemPricing& pricing) const
{
	int volumeUnits = 0;
	int looseUnits = count;

	if(pricing.d_volumeQty > 0)
	{
		volumeUnits = count / pricing.d_volumeQty;
		looseUnits = count - volumeUnits * pricing.d_volumeQty;
	}

	return (looseUnits*pricing.d_unitPrice +
			volumeUnits*pricing.d_volumePrice);
}

// vim:tw=78:ts=4:ft=cpp:et:
