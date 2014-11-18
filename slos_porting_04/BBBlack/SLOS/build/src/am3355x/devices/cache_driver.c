
#include "../../devices/ddf_frame.h"
#include "../devices/ddf_types.h"
#include "cache_driver.h"
#include "../headers/reg.h"

typedef struct 
{
unsigned int uid;      /* lock[0] = COM1 lock[1] = COM2 ........... */
} internal_cachestr;

internal_cachestr	node;

#if 0
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
#endif
void cache_init(void)
{
	/*icache_enable();
	dcache_enable();
	l2cache_enable();*/
	return;
}
UID cache_open(unsigned int major,unsigned int com)
{
	if (major == DEVICE_CACHE_BBBLACK){
		node.uid = uid_generate();
		return node.uid;
	}
	return DEVICE_NEXT;
}

int cache_close(UID id) 
{
  if (node.uid==id) 
  { 	
  node.uid = NONE;
  return DEVICE_SUCCESS;
  }

return DEVICE_UNKNOWN;
}


int read_cache_type_reg(void)
{
	volatile int regval;
	asm("MRC p15, 0, %[result], c0, c0, 1" : [result] "=r" (regval));
	
	return regval;
}

int read_cache_level_id_reg(void)
{
        volatile int regval;
        asm("MRC p15, 1, %[result], c0, c0, 1" : [result] "=r" (regval));

	return regval;
}

int read_cache_size_id_reg(UID id)
{
	volatile int regval; 
	
	int select = (id >> CACHE_SIZE_SELECT_SHIFT) & CACHE_SIZE_SELECT_MASK;

	switch(select){
		case SELECT_L2_CACHE:{
		/* Find the size of L2 Cache Unified cache */
			regval = SELECT_L2_CACHE;
			break;
		}
	
		case SELECT_L1_DCACHE:{
		/* Find the size of L1 D cache */
			regval = SELECT_L1_DCACHE;
			break;
		}
		case SELECT_L1_ICACHE:{
		/* Find the size of L1 I cache */
			regval = SELECT_L1_ICACHE;
			break;
		}
	}

	asm("MCR p15, 2, %[value], c0, c0, 0" : : [value] "r" (regval));
	asm("ISB");
	asm("MRC p15, 1, %[result], c0, c0, 0" : [result] "=r" (regval));
	asm("ISB");
		
	return regval;
}

int cache_read_reg(UID id)
{
	int select;
	select = id & ID_MASK;
	switch(select){
	
		case READ_CACHE_TYPE:
			return read_cache_type_reg();
		case READ_CACHE_LEVEL_ID:
			return read_cache_level_id_reg();
		case READ_CACHE_SIZE_ID:
			return read_cache_size_id_reg(id);
	} 
	
}
