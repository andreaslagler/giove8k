/*
Copyright (C) 2023 Andreas Lagler

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef EDIT_MENU_H
#define EDIT_MENU_H

#include <stdint.h>
#include <optional.h>
#include <variant.h>
#include <memory.h>
#include <functional.h>

#include "edit_menu_enums.h"
#include "param_database.h"
#include "application_event.h"




class EditMenu
{
    public:
    
    EditMenu(ParamDatabase& params, function<void(const ApplicationEvent&)>& eventHandler) : m_state(in_place_type_t<MenuStateIdle>()), m_params(params), m_eventHandler(eventHandler)
    {}

    constexpr EditMenuState getState() const
    {
        return static_cast<EditMenuState>(m_state.index());
    }
    
    void onEditButton();
    void onExitButton();
    void onBank1Button();
    void onBank2Button();
    void onBank3Button();
    void onBank4Button();
    void onBank5Button();
    void onBank6Button();
    void onBank7Button();
    void onBank8Button();
    void onUpButton(const bool value);
    void onDownButton(const bool value);
    void clock();

    private:

    
    Optional<UiParamIdx> getSelectedParam();

    struct MenuStateBase
    {
        auto onEditButton();
        auto onExitButton();
        auto onBank1Button();
        auto onBank2Button();
        auto onBank3Button();
        auto onBank4Button();
        auto onBank5Button();
        auto onBank6Button();
        auto onBank7Button();
        auto onBank8Button();
        void clock();
        Optional<UiParamIdx> getSelectedParam() const { return nullopt; }
    };

    struct MenuStateIdle : public MenuStateBase
    {
        auto onEditButton();
    };

    struct MenuStateEdit : public MenuStateBase
    {
        auto onEditButton();
        auto onBank1Button();
        auto onBank2Button();
        auto onBank3Button();
        auto onBank4Button();
        auto onBank5Button();
        auto onBank6Button();
        auto onBank7Button();
        auto onBank8Button();
    };

    struct MenuStateBank1 : public MenuStateBase
    {
        auto onBank1Button();
        Optional<UiParamIdx> getSelectedParam() const;
        static constexpr uint8_t s_nofItems = 11;
        uint8_t m_selectedItem = 0;
    };

    struct MenuStateBank2 : public MenuStateBase
    {
        auto onBank2Button();
        Optional<UiParamIdx> getSelectedParam() const;
        static constexpr uint8_t s_nofItems = 12;
        uint8_t m_selectedItem = 0;
    };
    
    struct MenuStateBank3 : public MenuStateBase
    {
        auto onBank3Button();
        Optional<UiParamIdx> getSelectedParam() const;
        static constexpr uint8_t s_nofItems = 5;
        uint8_t m_selectedItem = 0;
    };
    
    struct MenuStateBank4 : public MenuStateBase
    {
        auto onBank4Button();
        Optional<UiParamIdx> getSelectedParam() const;
        static constexpr uint8_t s_nofItems = 11;
        uint8_t m_selectedItem = 0;
    };
    
    struct MenuStateBank5 : public MenuStateBase
    {
        auto onBank5Button();
        Optional<UiParamIdx> getSelectedParam() const;
        static constexpr uint8_t s_nofItems = 13;
        uint8_t m_selectedItem = 0;
    };
    
    struct MenuStateBank6 : public MenuStateBase
    {
        auto onBank6Button();
        Optional<UiParamIdx> getSelectedParam() const;
        static constexpr uint8_t s_nofItems = 5;
        uint8_t m_selectedItem = 0;
    };
    
    struct MenuStateBank7 : public MenuStateBase
    {
    };
    
    struct MenuStateBank8 : public MenuStateBase
    {
    };
    
    using MenuState = Variant<
    MenuStateIdle,
    MenuStateEdit,
    MenuStateBank1,
    MenuStateBank2,
    MenuStateBank3,
    MenuStateBank4,
    MenuStateBank5,
    MenuStateBank6,
    MenuStateBank7,
    MenuStateBank8>;

    MenuState m_state;
    
            constexpr void setParam(const UiParamIdx& param)
            {
                m_eventHandler(ApplicationEvent(in_place_type_t<UiParamChangeEvent>(), param, m_params.getParamValue(param)));
            }
            
            constexpr void showParam(const UiParamIdx& param)
            {
                m_eventHandler(ApplicationEvent(in_place_type_t<UiParamShowEvent>(), param, m_params.getParamValue(param)));
            }

            void showSelectedParam()
            {
                const auto param = getSelectedParam();
                if (param)
                {
                    showParam(*param);
                }
            }
            
            constexpr void showState()
            {
               m_eventHandler(ApplicationEvent(in_place_type_t<EditMenuEvent>(), getState()));
            }
            
            
            void incSelectedParam();
            void decSelectedParam();

            union
            {
                uint8_t m_flags;
                struct __attribute__((packed))
                {
                    bool m_upButtonPushed:1 = false;
                    bool m_downButtonPushed :1= false;
                    bool m_upFast:1 = false;
                    bool m_downFast:1= false;
                };
            };

            // Access to application parameter database
            ParamDatabase& m_params;
            
            // Access to application event handler
            function<void(const ApplicationEvent&)>& m_eventHandler;
};

# endif