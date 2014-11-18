

#define ICacheEnableShift 0xC
#define DCacheEnableShift 0x2

void dcache_enable()
{
        volatile int regval;
        
        /* read the Control register */
        asm("MRC p15, 0, %[result], c1, c0, 0" : [result] "=r" (regval));

        regval |= (0x1 << DCacheEnableShift);

        asm ("MCR p15, 0, %[value], c1, c0, 0" : : [value] "r" (regval));

        return;
}

void icache_enable()
{
	volatile int regval;

	/* read the Control register */
	asm("MRC p15, 0, %[result], c1, c0, 0" : [result] "=r" (regval));

	regval |= (0x1 << ICacheEnableShift);

	asm ("MCR p15, 0, %[value], c1, c0, 0" : : [value] "r" (regval));

	return;
}

void cache_enable()
{
	icache_enable();
	dcache_enable();
	/*l2cache_enable();*/
	return;
}
#define IMinLine	0xF	/* mask for IMinLine value*/
#define IPolicyShift	0xe	/* shift for IPolicy */
#define IPolicyMask	0x3	/* 2 bit mask for IPolicyMask */
#define DMinLineShift	0x10	/* shift for DMinLine value */
#define DMinLineMask	0xf	/* 4 bit mask for DMinLine val */
#define CacheGranuleShift	0x18	/* shift for Cache Granule value */
#define CacheGranuleMask	0xf	/* 4 bit mask for Cache Granule val */

void read_cache_type(void)
{
	volatile int regval;
	int value;
	asm("MRC p15, 0, %[result], c0, c0, 1" : [result] "=r" (regval));
	
	value = regval & IMinLine;
	printf("the number of words of smallest line length in L1/L2 I cache is %d\n",value);
	
	value = (regval >> IPolicyShift) & IPolicyMask;
	
	printf("the L1 IPolicy is %d\n",value);
	
	value = (regval >> DMinLineShift) & DMinLineMask;
	printf("the number of words in L1/L2 D cache is %d\n",value);

	value = (regval >> CacheGranuleShift) & CacheGranuleMask;
	printf("the cache wb granule size is %d\n",value);

	return;
}
#define SeparateL1CacheMask	0x7
#define CL2Shift		0x3
#define CL2Mask			0x7
#define LoCShift		0x18
#define LoCMask			0x7
#define LoUShift		0x1B
#define LoUMask			0x7

void read_cache_level_id(void)
{
        volatile int regval;
        int value;
        asm("MRC p15, 1, %[result], c0, c0, 1" : [result] "=r" (regval));

	value = regval & SeparateL1CacheMask;
	if (value == 0x3)
		printf("separate caches at CL1\n");
	else
		printf("separate caches at CL1 value is %d\n", value);

	
	value = (regval >> CL2Shift) & CL2Mask;

	if (value == 0x4)
		printf("Unified Cache at Level 2\n");
	else
		printf("no cache at level 2 val is %d\n", value);

	value = (regval >> LoCShift) & LoCMask;
	if(value == 0x2)
		printf("Level of Coherencey is AMBA AXI interf.\n");
	else
		printf("LoC value is %d\n",value);

	value = (regval >> LoUShift) & LoUMask;
	if(value == 0x1)
		printf("Level of Unification is CL2\n");
	else
		printf("LoU value is %d\n",value);
		
	return;
}
#define SelectL2Cache	0x2
#define SelectL1DCache	0x0
#define SelectL1ICache	0x1

#define LineSizeMask	0x7
#define AssocShift	0x7
#define AssocMask	0x3FF
#define SetShift	0xD
#define SetMask		0x07FF	/* the max is 7FF */
#define WAShift		0x1C
#define RAShitf		0x1D
#define WBShitf		0x1E
#define WTShitf		0x1F


void read_cache_size_id()
{
	volatile int regval; 
	
	/* Find the size of L2 Cache Unified cache */
	regval = SelectL2Cache;

	asm("MCR p15, 2, %[value], c0, c0, 0" : : [value] "r" (regval));

	asm("MRC p15, 1, %[result], c0, c0, 0" : [result] "=r" (regval));

	value = regval & LineSizeMask;
	printf("The L2 Cache Line Size is %d\n"value);

	value = (regval >> AssocShift) & AssocMask;
	printf("The L2 Cache Way Size is %d\n", value  + 1);

	value = (regval >> SetShift) & SetMask;
	printf("The L2 Cache number of Sets is %d\n", value  + 1);


	if((regval >> WAShift) & 0x1)
		printf("L2 supports write allocation\n");
	else
		printf("L2 doesn't support write allocation\n");
	
	if((regval >> RAShift) & 0x1)
		printf("L2 supports read allocation\n");
	else
		printf("L2 doesn't support read allocation\n");

	if((regval >> WBShift) & 0x1)
		printf("L2 supports write back\n");
	else
		printf("L2 doesn't support write back\n");

	if((regval >> WTShift) & 0x1)
		printf("L2 supports write through\n");
	else
		printf("L2 doesn't support write through\n");


	/* Find the size of L1 instruction cache */
        regval = SelectL1ICache;

        asm("MCR p15, 2, %[value], c0, c0, 0" : : [value] "r" (regval));

        asm("MRC p15, 1, %[result], c0, c0, 0" : [result] "=r" (regval));

        value = regval & LineSizeMask;
        printf("The L1 ICache Line Size is %d\n"value);

        value = (regval >> AssocShift) & AssocMask;
        printf("The L1 ICache Way Size is %d\n", value  + 1);

        value = (regval >> SetShift) & SetMask;
        printf("The L1 ICache number of Sets is %d\n", value  + 1);

        
        if((regval >> WAShift) & 0x1)
                printf("L1I supports write allocation\n");
        else
                printf("L1I doesn't support write allocation\n");

        if((regval >> RAShift) & 0x1)
                printf("L1I supports read allocation\n");
        else
                printf("L1I doesn't support read allocation\n");

        if((regval >> WBShift) & 0x1)
                printf("L1I supports write back\n");
        else
                printf("L1I doesn't support write back\n");

        if((regval >> WTShift) & 0x1)
                printf("L1I supports write through\n");
        else
                printf("L1I doesn't support write through\n");


       /* Find the size of L1 data cache */
        regval = SelectL1DCache;

        asm("MCR p15, 2, %[value], c0, c0, 0" : : [value] "r" (regval));

        asm("MRC p15, 1, %[result], c0, c0, 0" : [result] "=r" (regval));

        value = regval & LineSizeMask;
        printf("The L1 DCache Line Size is %d\n"value);

        value = (regval >> AssocShift) & AssocMask;
        printf("The L1 DCache Way Size is %d\n", value  + 1);

        value = (regval >> SetShift) & SetMask;
        printf("The L1 DCache number of Sets is %d\n", value  + 1);


        if((regval >> WAShift) & 0x1)
                printf("L1D supports write allocation\n");
        else
                printf("L1D doesn't support write allocation\n");

        if((regval >> RAShift) & 0x1)
                printf("L1D supports read allocation\n");
        else
                printf("L1D doesn't support read allocation\n");

        if((regval >> WBShift) & 0x1)
                printf("L1D supports write back\n");
        else
                printf("L1D doesn't support write back\n");

        if((regval >> WTShift) & 0x1)
                printf("L1D supports write through\n");
        else
                printf("L1D doesn't support write through\n");

}

cache_main()
{
	/*flush_cache();*/
	cache_enable();
	read_cache_type();
	read_cache_level_id();
	read_cache_size_id();
}
