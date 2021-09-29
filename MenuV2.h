#pragma once

#include <vector>
#include <string>
#include <functional>
#include <ScriptHookV/inc/natives.h>
#include "keyboard.h"

class MenuNode
{
public:
	MenuNode(std::string new_label, MenuNode* parent, std::function<void(MenuNode*)> cb = nullptr) {
		this->label = new_label;
		this->parent = parent;
		this->cb = cb;
	}
	MenuNode* Add(std::string label, std::function<void(MenuNode*)> cb = nullptr) {
		MenuNode* node = new MenuNode(label, this, cb);
		children.push_back(node);
		return node;
	}

	MenuNode* parent;
	std::string label;
	std::vector<MenuNode*> children;
	std::function<void(MenuNode*)> cb;
};

class Menu {
public:
	Menu(MenuNode* root) {
		this->root = root;
		this->current = root->children[0];
		this->currentIndex = 0;
	}

	void moveDown() {
		if (!this->current->parent) return;

		currentIndex++;

		if (currentIndex > this->current->parent->children.size() - 1) {
			currentIndex = 0;
		}

		this->current = this->current->parent->children[currentIndex];
	}

	void moveUp() {
		if (!this->current->parent) return;

		currentIndex--;

		if (currentIndex < 0) {
			currentIndex = this->current->parent->children.size() - 1;
		}

		this->current = this->current->parent->children[currentIndex];
	}

	void enter() {
		if (this->current->cb) {
			this->current->cb(this->current);
		}
		if (this->current->children.size() == 0) return;
		this->current = this->current->children[0];
		this->currentIndex = 0;
	}

	void exit() {
		if (!this->current->parent) return;
		this->current = this->current->parent;
		this->currentIndex = 0;
	}

	std::vector<MenuNode*> getCurrentMenu() {
		if (this->current->parent) {
			return this->current->parent->children;
		}
		return {};
	}

	void printMenu() {
		std::cout << current->label << std::endl;
	}

	MenuNode* root;
	MenuNode* current;
	int currentIndex;
};

class MenuHandler {
	public:
		std::string headerText;

		float screenWidth = 1280;
		float screenHeight = 720;

		float menuMarginLeft = scaleX(15.0);
		float menuMarginTop = scaleY(15.0);

		float textMarginLeft = scaleX(4.0);

		float headerWidth = scaleX(400.0);
		float headerHeight = scaleY(45.0);

		float buttonWidth = scaleX(400.0);
		float buttonHeight = scaleY(35.0);

		float buttonSpace = scaleY(0.0);

		float headerFontScale = 0.6f;
		float buttonFontScale = 0.4f;

		int headerFont = 1;
		int buttonFont = 0;

		int headerBgColor[4] = { 10, 10, 10, 255 };
		int headerTextColor[4] = { 245, 245, 245, 255 };

		int defaultBgColor[4] = { 56, 95, 94, 210 };
		int defaultBgHighlightColor[4] = { 218, 242, 216, 255 };
		int defaultTextColor[4] = { 243, 255, 255, 255 };
		int defaultTextHighlightColor[4] = { 10, 10, 10, 255 };

		Menu* menu;

		int paginationStart = 0;
		int paginationEnd = 0;
		int itemsPerPage = 10;

		bool _disableMenuThisFrame;

		MenuHandler::MenuHandler(Menu *menu, std::string headerText) {
			this->menu = menu;
			this->headerText = headerText;
		}

		void MenuHandler::update()
		{
			this->updateScreenResolution();
			this->HandleKeys();
			this->HandlePagination();

			if (this->_disableMenuThisFrame) {
				this->_disableMenuThisFrame = false;
				return;
			}

			// Header
			this->drawText(headerText, headerFontScale, headerTextColor, menuMarginLeft + textMarginLeft, menuMarginTop + headerHeight * 0.2f, headerFont);
			this->drawBackground(menuMarginLeft, menuMarginTop, headerWidth, headerHeight, headerBgColor);

			int itemCount = 0;
			std::vector<MenuNode*> currentMenu = this->menu->getCurrentMenu();

			if (currentMenu.size() == 0) return;

			/*for (MenuNode * node: this->menu->getCurrentMenu()) {*/
			for (int i = this->paginationStart; i < this->paginationEnd; i++)
			{
				MenuNode* node = currentMenu.at(i);
				bool active = this->menu->currentIndex == i;

				int* bgColor = active ? this->defaultBgHighlightColor : this->defaultBgColor;
				int* textColor = active ? this->defaultTextHighlightColor : this->defaultTextColor;

				float posX = menuMarginLeft;
				float posY = menuMarginTop + (buttonHeight + buttonSpace) * itemCount;
				if (!headerText.empty()) posY += headerHeight;

				std::string suffix = node->children.size() > 0 ? " >" : "";
				this->drawText(node->label + suffix, buttonFontScale, textColor, menuMarginLeft + textMarginLeft, posY + buttonHeight * 0.2f, buttonFont);
				this->drawBackground(posX, posY, buttonWidth, buttonHeight, bgColor);
				itemCount++;
			}
		}

		void MenuHandler::HandleKeys() {
			if (IsKeyJustUp(VK_NUMPAD2)) {
				this->menu->moveDown();
			}
			if (IsKeyJustUp(VK_NUMPAD8)) {
				this->menu->moveUp();
			}
			if (IsKeyJustUp(VK_NUMPAD5)) {
				this->menu->enter();
			}
			if (IsKeyJustUp(VK_NUMPAD0)) {
				this->menu->exit();
			}
		}

		void MenuHandler::HandlePagination() {
			std::vector<MenuNode*> currentMenu = this->menu->getCurrentMenu();
			int currentIndex = this->menu->currentIndex;

			if (currentIndex > this->paginationEnd-1) {
				this->paginationStart += this->itemsPerPage;
				this->paginationEnd = this->paginationEnd + this->itemsPerPage > currentMenu.size() ? currentMenu.size() : this->paginationEnd + this->itemsPerPage;
			}
			else if (currentIndex < this->paginationStart) {
				this->paginationStart = this->paginationStart - this->itemsPerPage < 0 ? 0 : this->paginationStart - this->itemsPerPage;
				this->paginationEnd -= this->itemsPerPage;
			}

			// Wraps
			if (currentIndex == 0) {
				this->paginationStart = 0;
				this->paginationEnd = this->paginationStart + this->itemsPerPage > currentMenu.size() ? currentMenu.size() : this->paginationStart + this->itemsPerPage;
			}
			else if (currentIndex == currentMenu.size() - 1) {
				this->paginationStart = currentMenu.size() > this->itemsPerPage ? currentMenu.size() - this->itemsPerPage : 0;
				this->paginationEnd = currentMenu.size();
			}
		}

		void MenuHandler::drawBackground(float posX, float posY, float width, float height, int color[4])
		{
			GRAPHICS::DRAW_RECT(posX + width * 0.5f, posY + height * 0.5f, width, height, color[0], color[1], color[2], color[3]);
		}

		void MenuHandler::drawText(std::string text, float size, int color[4], float posX, float posY, int font)
		{
			UI::SET_TEXT_FONT(font);
			UI::SET_TEXT_SCALE(0.0, size);
			UI::SET_TEXT_COLOUR(color[0], color[1], color[2], color[3]);
			UI::SET_TEXT_CENTRE(0);
			UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)text.c_str());
			UI::_DRAW_TEXT(posX, posY);
		}

		float MenuHandler::scaleX(float value)
		{
			if (screenWidth <= 0) this->updateScreenResolution();

			return value / screenWidth;
		}

		float MenuHandler::scaleY(float value)
		{
			if (screenHeight <= 0) this->updateScreenResolution();

			return value / screenHeight;
		}

		void MenuHandler::updateScreenResolution()
		{
			//int width, height;
			//GRAPHICS::_GET_SCREEN_ACTIVE_RESOLUTION(&width, &height);

			this->screenWidth = (float)1280;
			this->screenHeight = (float)720;
		};

		void MenuHandler::disableMenuThisFrame()
		{
			this->_disableMenuThisFrame = true;
		};
};