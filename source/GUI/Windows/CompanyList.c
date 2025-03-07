#include "CompanyList.h"

void drawCompanyList(AppPlatform* platform, AppState* current_app_state, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Company List", nk_rect(50, 50, 450, 500),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		char buffer[BUF_SIZE] = "";
		nk_layout_row_static(platform->ctx, 30, 100, 1);
		nk_label(platform->ctx, "Factories:", NK_TEXT_LEFT);

		for (int i = 0; i < current_app_state->companies_num; i++)
		{
			nk_layout_row_static(platform->ctx, 30, 200, 2);
			snprintf(buffer, BUF_SIZE, "Company #%i", current_app_state->companies[i].id);
			nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
			if (nk_button_label(platform->ctx, "Show"))
			{
				addNewPopupWindow(platform->first_window, COMPANY_MENU, &current_app_state->companies[i]);
			}
		}
		
	}
	nk_end(platform->ctx);
}