#include "DSCEngine/system/hardware.hpp"

#include "DSCEngine/debug/assert.hpp"
#include "DSCEngine/debug/log.hpp"

using namespace DSC::Hardware;

char* const DSC::Hardware::BanksReg = (char* const)0x04000240;

DSC::Hardware::VramBank::VramBank(char bank_name) : bank_name(bank_name)
{
	nds_assert('A'<=bank_name && bank_name<='I');
}

VramBank& DSC::Hardware::VramBank::lcd() { is_lcd = true; return *this; }

VramBank& DSC::Hardware::VramBank::main() { is_lcd = false, is_main = true; return *this; }

VramBank& DSC::Hardware::VramBank::sub() { is_lcd = false, is_main = false; return *this; }

VramBank& DSC::Hardware::VramBank::background() { is_lcd = false,is_background = true; return *this; }

VramBank& DSC::Hardware::VramBank::sprite() { is_lcd = false, is_background = false; return *this; }

VramBank& DSC::Hardware::VramBank::vram() { is_lcd = false, is_vram = true; return *this; }

VramBank& DSC::Hardware::VramBank::ext_palette() { is_lcd = false, is_vram = false; return *this; }

VramBank& DSC::Hardware::VramBank::slot(int slot_number) 
{
	nds_assert(0<=slot_number && slot_number<=3);
	is_lcd = false, ofs = slot_number; 
	return *this; 
}

void DSC::Hardware::VramBank::config()
{
	if(is_lcd) 
	{
		BanksReg[bank_name-'A'] = 0; return;
	}
	
	int mst=0;	
	
	if(is_main)
	{
		if(is_background && is_vram)
		{
			nds_assert(bank_name<='G');
			mst = 1;
			if(bank_name=='E')
			{			
				ofs = 0;			
			}					
		}		
		else if(!is_background && is_vram)
		{
			mst = 2;
			if(bank_name=='A' || bank_name=='B') 
				ofs &= 1;
			else if(bank_name=='E') 
				ofs = 0;
			else 
				nds_assert(false, "Wrong bank MainBgExtPal");
		}
		else if(is_background && !is_vram)
		{
			nds_assert('E'<=bank_name && bank_name<='G');
			mst = 4;
			if(bank_name!='E') ofs &= 1;
		}
		else if(!is_background && !is_vram)
		{
			nds_assert(bank_name=='F' || bank_name=='G');
			mst = 5; ofs = 0;
		}
	}
	else 		
	{
		ofs = 0;
		if(is_background && is_vram)
		{
			if(bank_name=='C') 
				mst = 4;
			else if(bank_name>='H')
				mst = 1;
			else nds_assert(false, "Wrong bank SubBgVram");
		}
		else if(!is_background && is_vram)
		{
			if(bank_name=='D')
				mst = 4;
			else if(bank_name=='I')
				mst = 2;
			else nds_assert(false, "Wrong bank SubObjVram");
		}
		else if(is_background && !is_vram)
		{
			nds_assert(bank_name=='H');
			mst = 2;
		}
		else if(!is_background && !is_vram)
		{
			nds_assert(bank_name=='I');
			mst = 3;
		}
	}	
	
	BanksReg[bank_name-'A'] = 0x80 | mst | (ofs<<3);
}
	
void DSC::Hardware::VramBank::enable() { BanksReg[bank_name-'A'] |= 0x80; }

void DSC::Hardware::VramBank::disable() { BanksReg[bank_name-'A'] &= 0x7f; }

VramBank& DSC::Hardware::VramBank::save_state()
{
	backup = BanksReg[bank_name-'A'];
	return *this;
}

void DSC::Hardware::VramBank::restore()
{	
	BanksReg[bank_name-'A'] = backup;
}
	