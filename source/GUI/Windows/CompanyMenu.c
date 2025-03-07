#include "CompanyMenu.h"

void drawCompanyMenu(AppPlatform* const platform, Company* const company, const char* const name)
{
	if (nk_begin_titled(platform->ctx, name, "Company Menu", nk_rect(50, 50, 450, 500),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		char buffer[BUF_SIZE] = "";
		
		nk_layout_row_static(platform->ctx, 30, 200, 2);
		nk_label(platform->ctx, "Wealth:", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "$%i", company->wealth);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
		

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		nk_label(platform->ctx, "Controlled Factories:", NK_TEXT_LEFT);

		for (int i = 0; i < company->controlled_factories_num; i++)
		{
			const Factory* curr_fact = company->controlled_factories[i];
			nk_layout_row_static(platform->ctx, 30, 200, 2);
			nk_label(platform->ctx, getNameProductionRecipe(curr_fact->productionRecipe), NK_TEXT_LEFT);
			if (nk_button_label(platform->ctx, "Show"))
			{
				addNewPopupWindow(platform->first_window, FACTORY_MENU, curr_fact);
			}
		}
		
	}
	nk_end(platform->ctx);
}