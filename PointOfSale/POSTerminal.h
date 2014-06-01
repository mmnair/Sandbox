#ifndef POS_TERMINAL_H
#define POS_TERMINAL_H

struct ItemPricing
{
	double d_unitPrice;
	int d_volumeQty;
	double d_volumePrice;
};

class POSTerminal
{
	public:
		POSTerminal();
		virtual ~POSTerminal();

		void setPrice(char item, double unitPrice,
				int volumeQty, double volumePrice);

		void scanItem(char item);
        void scanMultipleItems(const char *items);
        double getTotal() const;

	private:
        //No Assignment or copying of the class
        POSTerminal(const POSTerminal &);
        POSTerminal& operator=(const POSTerminal &);
        
		double getSingleItemTotal(int count, 
				const ItemPricing& pricing) const;

        //data members
		int d_itemCounts[256];
		ItemPricing d_pricingTable[256];

};

#endif //POS_TERMINAL_H

// vim:tw=78:ts=4:ft=cpp:et:
