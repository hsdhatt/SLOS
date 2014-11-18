#include "../core/mutex.h"

#include "../headers/api_types.h"
#include "../devices/ddf_io.h"
#include "../am3355x/devices/ddf_types.h"

#include "../am3355x/events/swis.h"
#include "../headers/api_device.h"

device_treestr *cache_host;
UID cache_id;


#define ICACHE_ENABLE_SHIFT 0xC
#define DCACHE_ENABLE_SHIFT 0x2

/* Bit Field definitions for Cache type Register */
#define IM_INLINE		0xF	/* mask for IM_INLINE value*/
#define IPOLICY_SHIFT		0xe	/* shift for IPOLICY */
#define IPOLICY_MASK		0x3	/* 2 bit mask for IPOLICYMASK */
#define DM_INLINE_SHIFT		0x10	/* shift for DMINLINE value */
#define DM_INLINE_MASK		0xf	/* 4 bit mask for DMINLINE val */
#define CACHE_GRANULE_SHIFT	0x18	/* shift for Cache Granule value */
#define CACHE_GRANULE_MASK	0xf	/* 4 bit mask for Cache Granule val */

/* Bit Field definitions for cache level register */
#define SEPARATE_L1_CACHE	0x3
#define SEPARATE_L1_CACHE_MASK	0x7
#define CL2_UNIFIED		0x4
#define CL2_SHIFT		0x3
#define CL2_MASK		0x7
#define LOC_SHIFT		0x18
#define LOC_MASK		0x7
#define LOU_SHIFT		0x1B
#define LOU_MASK		0x7

/* Bit Field definitions for cache size register */
#define LINE_SIZE_MASK	0x7
#define ASSOC_SHIFT	0x3
#define ASSOC_MASK	0x3FF
#define SET_SHIFT	0xD
#define SET_MASK	0x07FF	/* the max is 7FF */
#define WA_SHIFT	0x1C
#define RA_SHIFT	0x1D
#define WB_SHIFT	0x1E
#define WT_SHIFT	0x1F

BOOL openCACHE(void) 
{ 
	/* enable the caches */
	cache_host = eventIODeviceOpen(&cache_id,DEVICE_CACHE_BBBLACK,0);

	if (cache_host==0)
		return FALSE;
	else
		return TRUE; 
}

void read_cache_type(void)
{
	volatile int regval;
	int value;
	cache_id = READ_CACHE_TYPE;
	regval = eventIODeviceReadReg(cache_host,cache_id);

	value = regval & IM_INLINE;
	prettyPrint("the number of words of smallest line length in L1/L2 I cache is %d\n",value);
	
	value = (regval >> IPOLICY_SHIFT) & IPOLICY_MASK;
	
	prettyPrint("the L1 IPOLICY is %d\n",value);
	
	value = (regval >> DM_INLINE_SHIFT) & DM_INLINE_MASK;
	prettyPrint("the number of words in L1/L2 D cache is %d\n",value);

	value = (regval >> CACHE_GRANULE_SHIFT) & CACHE_GRANULE_MASK;
	prettyPrint("the cache wb granule size is %d\n",value);

	return;
}


void read_cache_level_id(void)
{
        volatile int regval;
        int value;
	cache_id = READ_CACHE_LEVEL_ID; /* READ_CACHE_TYPE */
        regval = eventIODeviceReadReg(cache_host,cache_id);

	value = regval & SEPARATE_L1_CACHE_MASK;
	if (value == SEPARATE_L1_CACHE)
		prettyPrint("separate caches at CL1\n");
	else
		prettyPrint("separate caches at CL1 value is %d\n", value);

	
	value = (regval >> CL2_SHIFT) & CL2_MASK;

	if (value == CL2_UNIFIED)
		prettyPrint("Unified Cache at Level 2\n");
	else
		prettyPrint("no cache at level 2 val is %d\n", value);

	value = (regval >> LOC_SHIFT) & LOC_MASK;
	if(value == 0x2)
		prettyPrint("Level of Coherencey is AMBA AXI interf.\n");
	else
		prettyPrint("LoC value is %d\n",value);

	value = (regval >> LOU_SHIFT) & LOU_MASK;
	if(value == 0x1)
		prettyPrint("Level of Unification is CL2\n");
	else
		prettyPrint("LoU value is %d\n",value);
		
	return;
}



void read_cache_size_id()
{
	volatile int regval, value; 
	cache_id = 0x0;

	/* Find the size of L2 Cache Unified cache */
	cache_id |= (SELECT_L2_CACHE << CACHE_SIZE_SELECT_SHIFT) | READ_CACHE_SIZE_ID;
	regval = eventIODeviceReadReg(cache_host,cache_id);

	value = regval & LINE_SIZE_MASK;
	prettyPrint("The L2 Cache Line Size is %d\n",value);

	value = (regval >> ASSOC_SHIFT) & ASSOC_MASK;
	prettyPrint("The L2 Cache Way Size is %d\n", value  + 1);

	value = (regval >> SET_SHIFT) & SET_MASK;
	prettyPrint("The L2 Cache number of Sets is %d\n", value  + 1);


	if((regval >> WA_SHIFT) & 0x1)
		prettyPrint("L2 supports write allocation\n");
	else
		prettyPrint("L2 doesn't support write allocation\n");
	
	if((regval >> RA_SHIFT) & 0x1)
		prettyPrint("L2 supports read allocation\n");
	else
		prettyPrint("L2 doesn't support read allocation\n");

	if((regval >> WB_SHIFT) & 0x1)
		prettyPrint("L2 supports write back\n");
	else
		prettyPrint("L2 doesn't support write back\n");

	if((regval >> WT_SHIFT) & 0x1)
		prettyPrint("L2 supports write through\n");
	else
		prettyPrint("L2 doesn't support write through\n");


	/* Find the size of L1 instruction cache */
	cache_id = (SELECT_L1_ICACHE << CACHE_SIZE_SELECT_SHIFT) | READ_CACHE_SIZE_ID;
	regval = eventIODeviceReadReg(cache_host,cache_id);

        value = regval & LINE_SIZE_MASK;
        prettyPrint("The L1 ICache Line Size is %d\n",value);

        value = (regval >> ASSOC_SHIFT) & ASSOC_MASK;
        prettyPrint("The L1 ICache Way Size is %d\n", value  + 1);

        value = (regval >> SET_SHIFT) & SET_MASK;
        prettyPrint("The L1 ICache number of Sets is %d\n", value  + 1);

        
        if((regval >> WA_SHIFT) & 0x1)
                prettyPrint("L1I supports write allocation\n");
        else
                prettyPrint("L1I doesn't support write allocation\n");

        if((regval >> RA_SHIFT) & 0x1)
                prettyPrint("L1I supports read allocation\n");
        else
                prettyPrint("L1I doesn't support read allocation\n");

        if((regval >> WB_SHIFT) & 0x1)
                prettyPrint("L1I supports write back\n");
        else
                prettyPrint("L1I doesn't support write back\n");

        if((regval >> WT_SHIFT) & 0x1)
                prettyPrint("L1I supports write through\n");
        else
                prettyPrint("L1I doesn't support write through\n");


       /* Find the size of L1 data cache */
	cache_id = (SELECT_L1_DCACHE << CACHE_SIZE_SELECT_SHIFT) | READ_CACHE_SIZE_ID;
	regval = eventIODeviceReadReg(cache_host,cache_id);


        value = regval & LINE_SIZE_MASK;
        prettyPrint("The L1 DCache Line Size is %d\n",value);

        value = (regval >> ASSOC_SHIFT) & ASSOC_MASK;
        prettyPrint("The L1 DCache Way Size is %d\n", value  + 1);

        value = (regval >> SET_SHIFT) & SET_MASK;
        prettyPrint("The L1 DCache number of Sets is %d\n", value  + 1);


        if((regval >> WA_SHIFT) & 0x1)
                prettyPrint("L1D supports write allocation\n");
        else
                prettyPrint("L1D doesn't support write allocation\n");

        if((regval >> RA_SHIFT) & 0x1)
                prettyPrint("L1D supports read allocation\n");
        else
                prettyPrint("L1D doesn't support read allocation\n");

        if((regval >> WB_SHIFT) & 0x1)
                prettyPrint("L1D supports write back\n");
        else
                prettyPrint("L1D doesn't support write back\n");

        if((regval >> WT_SHIFT) & 0x1)
                prettyPrint("L1D supports write through\n");
        else
                prettyPrint("L1D doesn't support write through\n");

}

void C_EntryTaskCache()
{
	if (openCACHE() == TRUE){

		if (openHost(0) == TRUE){	/* openHost opens the console driver to be able to print */
			read_cache_type();
			read_cache_level_id();
			read_cache_size_id();
		}
	}

	while(1){;};	/* dummy while loop */
}
