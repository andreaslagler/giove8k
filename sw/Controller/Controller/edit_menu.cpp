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

#include "edit_menu.h"

#include <stdint.h>
#include <optional.h>
#include <variant.h>
#include <lookup_table.h>

auto EditMenu::MenuStateBase::onEditButton() { return Optional(MenuState(in_place_type_t<MenuStateIdle>())); }
auto EditMenu::MenuStateBase::onExitButton() { return Optional(MenuState(in_place_type_t<MenuStateIdle>())); }
auto EditMenu::MenuStateBase::onBank1Button() { return Optional<MenuState>(nullopt); }
auto EditMenu::MenuStateBase::onBank2Button() { return Optional<MenuState>(nullopt); }
auto EditMenu::MenuStateBase::onBank3Button() { return Optional<MenuState>(nullopt); }
auto EditMenu::MenuStateBase::onBank4Button() { return Optional<MenuState>(nullopt); }
auto EditMenu::MenuStateBase::onBank5Button() { return Optional<MenuState>(nullopt); }
auto EditMenu::MenuStateBase::onBank6Button() { return Optional<MenuState>(nullopt); }
auto EditMenu::MenuStateBase::onBank7Button() { return Optional<MenuState>(nullopt); }
auto EditMenu::MenuStateBase::onBank8Button() { return Optional<MenuState>(nullopt); }

void EditMenu::onUpButton(const bool value)
{
    // Check if down button is pushed
    if (m_downButtonPushed)
    {
        // Enter fast mode for DECREMENT when down button is already pushed and up button is now also pushed
        m_downFast = value;
    }
    else if ((m_upButtonPushed = value))
    {
        // Down button is not pushed and up button is pushed --> increment current edit menu parameter
        incSelectedParam();
    }
    else
    {
        // Down button is not pushed and up button is not pushed
        m_upFast = false;
    }
}

void EditMenu::onDownButton(const bool value)
{
    // Check if up button is pushed
    if (m_upButtonPushed)
    {
        // Enter fast mode for INCREMENT when down button is already pushed and up button is now also pushed
        m_upFast = value;
    }
    else if ((m_downButtonPushed = value))
    {
        // Up button is not pushed and down button is pushed --> decrement current edit menu parameter
        decSelectedParam();
    }
    else
    {
        // Up button is not pushed and down button is not pushed
        m_downFast = false;
    }
}

void EditMenu::clock()
{
    if (m_upFast)
    {
        incSelectedParam();
    }

    if (m_downFast)
    {
        decSelectedParam();
    }
}

void EditMenu::incSelectedParam()
{
    if(auto paramOpt = getSelectedParam())
    {
        auto& param = *paramOpt;
        const bool paramChanged = visit(
        [](auto& value) -> bool
        {
            bool ret = false;
            using Value = decay_t<decltype(value)>;
            if constexpr (is_enum_v<Value>)
            {
                using IntValue = underlying_type_t<Value>;
                if (static_cast<IntValue>(value) <= static_cast<IntValue>(Value::MAX))
                {
                    value = static_cast<Value>(static_cast<IntValue>(value) + static_cast<IntValue>(1));
                    ret = true;
                }
            }
            else
            {
                ret = value.increment();
            }
            return ret;
        },
        m_params.getParamValue(param));

        if (paramChanged)
        {
            setParam(param);
        }

        showParam(param);
    }
}

void EditMenu::decSelectedParam()
{
    if(auto paramOpt = getSelectedParam())
    {
        auto& param = *paramOpt;
        const bool paramChanged = visit(
        [](auto& value) -> bool
        {
            bool ret = false;
            using Value = decay_t<decltype(value)>;
            if constexpr (is_enum_v<Value>)
            {
                using IntValue = underlying_type_t<Value>;
                if (static_cast<IntValue>(value) > static_cast<IntValue>(Value::MIN))
                {
                    value = static_cast<Value>(static_cast<IntValue>(value) - static_cast<IntValue>(1));
                    ret = true;
                }
            }
            else
            {
                ret = value.decrement();
            }
            return ret;
        },
        m_params.getParamValue(param));

        if (paramChanged)
        {
            setParam(param);
        }

        showParam(param);
    }
}





auto EditMenu::MenuStateIdle::onEditButton()
{
    // When Edit button is pressed, change to menu state EDIT
    return Optional(EditMenu::MenuState(in_place_type_t<MenuStateEdit>()));
}

auto EditMenu::MenuStateEdit::onEditButton() { return Optional<MenuState>(nullopt); }
auto EditMenu::MenuStateEdit::onBank1Button() { return Optional(MenuState(in_place_type_t<MenuStateBank1>())); }
auto EditMenu::MenuStateEdit::onBank2Button() { return Optional(MenuState(in_place_type_t<MenuStateBank2>())); }
auto EditMenu::MenuStateEdit::onBank3Button() { return Optional(MenuState(in_place_type_t<MenuStateBank3>())); }
auto EditMenu::MenuStateEdit::onBank4Button() { return Optional(MenuState(in_place_type_t<MenuStateBank4>())); }
auto EditMenu::MenuStateEdit::onBank5Button() { return Optional(MenuState(in_place_type_t<MenuStateBank5>())); }
auto EditMenu::MenuStateEdit::onBank6Button() { return Optional(MenuState(in_place_type_t<MenuStateBank6>())); }
auto EditMenu::MenuStateEdit::onBank7Button() { return Optional(MenuState(in_place_type_t<MenuStateBank7>())); }
auto EditMenu::MenuStateEdit::onBank8Button() { return Optional(MenuState(in_place_type_t<MenuStateBank8>())); }

auto EditMenu::MenuStateBank1::onBank1Button()
{
    if (++m_selectedItem == s_nofItems)
    {
        m_selectedItem = 0;
    }
    return Optional<EditMenu::MenuState>(nullopt);
}

Optional<UiParamIdx> EditMenu::MenuStateBank1::getSelectedParam() const
{
    using Table = SparseLUT<PerformanceParam, uint8_t, s_nofItems>;

    constexpr static const PROGMEM Table table
    (
    PerformanceParam::NOFENTRIES,
    Table::Entry(0, PerformanceParam::PERFORMANCE_NAME),
    Table::Entry(1, PerformanceParam::PART_DETUNE),
    Table::Entry(2, PerformanceParam::OUTPUT_ASSIGN),
    Table::Entry(3, PerformanceParam::VOICE_ASSIGN),
    Table::Entry(4, PerformanceParam::SPLIT_POINT),
    Table::Entry(5, PerformanceParam::ARP_DESTINATION),
    Table::Entry(6, PerformanceParam::ARP_BEAT_PATTERN),
    Table::Entry(7, PerformanceParam::INDIVIDUAL_TRIG_STATE),
    Table::Entry(8, PerformanceParam::INDIVIDUAL_TRIG_DESTINATION),
    Table::Entry(9, PerformanceParam::INDIVIDUAL_TRIG_SOURCE_CHANNEL),
    Table::Entry(10, PerformanceParam::INDIVIDUAL_TRIG_SOURCE_NOTE)
    );

    return UiParamIdx(in_place_type_t<PerformanceParam>(), table.getP(m_selectedItem));
}

auto EditMenu::MenuStateBank2::onBank2Button()
{
    if (++m_selectedItem == s_nofItems)
    {
        m_selectedItem = 0;
    }
    return Optional<EditMenu::MenuState>(nullopt);
}

Optional<UiParamIdx> EditMenu::MenuStateBank2::getSelectedParam() const
{
    using Table = SparseLUT<PerformanceParam, uint8_t, s_nofItems>;

    constexpr static const PROGMEM Table table
    (
    PerformanceParam::NOFENTRIES,
    Table::Entry(0, PerformanceParam::ALGORITHM),
    Table::Entry(1, PerformanceParam::CONTROL1_ASSIGN),
    Table::Entry(2, PerformanceParam::CONTROL2_ASSIGN),
    Table::Entry(3, PerformanceParam::EXT_INST_SEND),
    Table::Entry(4, PerformanceParam::EXT_VOCAL_SEND),
    Table::Entry(5, PerformanceParam::VOICE_MODULATOR_DELAY_TYPE),
    Table::Entry(6, PerformanceParam::VOICE_MODULATOR_DELAY_SYNC),
    Table::Entry(7, PerformanceParam::ENSEMBLE_TYPE),
    Table::Entry(8, PerformanceParam::ENSEMBLE_SYNC),
    Table::Entry(9, PerformanceParam::VOCAL_MORPH_CONTROL),
    Table::Entry(10, PerformanceParam::VOCAL_MORPH_SENS),
    Table::Entry(11, PerformanceParam::VOCAL_MORPH_THRESHOLD)
    );

    return UiParamIdx(in_place_type_t<PerformanceParam>(), table.getP(m_selectedItem));
}

auto EditMenu::MenuStateBank3::onBank3Button()
{
    if (++m_selectedItem == s_nofItems)
    {
        m_selectedItem = 0;
    }
    return Optional<EditMenu::MenuState>(nullopt);
}

Optional<UiParamIdx> EditMenu::MenuStateBank3::getSelectedParam() const
{
    using Table = SparseLUT<PartParam, uint8_t, s_nofItems>;

    constexpr static const PROGMEM Table table
    (
    PartParam::NOFENTRIES,
    Table::Entry(0, PartParam::PART_TRANSPOSE),
    Table::Entry(1, PartParam::PART_MIDI_CHANNEL),
    Table::Entry(2, PartParam::CHORUS_SYNC),
    Table::Entry(3, PartParam::DELAY_SYNC),
    Table::Entry(4, PartParam::LFO_SYNC)
    );

    return UiParamIdx(in_place_type_t<PartParam>(), table.getP(m_selectedItem));
}

auto EditMenu::MenuStateBank4::onBank4Button()
{
    if (++m_selectedItem == s_nofItems)
    {
        m_selectedItem = 0;
    }
    return Optional<EditMenu::MenuState>(nullopt);
}

Optional<UiParamIdx> EditMenu::MenuStateBank4::getSelectedParam() const
{
    using Table = SparseLUT<PatchParam, uint8_t, s_nofItems>;

    constexpr static const PROGMEM Table table
    (
    PatchParam::NOFENTRIES,
    Table::Entry(0, PatchParam::PATCH_NAME),
    Table::Entry(1, PatchParam::MULTI_FX_TYPE),
    Table::Entry(2, PatchParam::DELAY_TYPE),
    Table::Entry(3, PatchParam::BEND_RANGE_UP),
    Table::Entry(4, PatchParam::BEND_RANGE_DOWN),
    Table::Entry(5, PatchParam::MORPH_BEND_ASSIGN),
    Table::Entry(6, PatchParam::UNISON_DETUNE),
    Table::Entry(7, PatchParam::ENV_TYPE_SOLO),
    Table::Entry(8, PatchParam::PATCH_GAIN),
    Table::Entry(9, PatchParam::EXT_TRIG_SWITCH),
    Table::Entry(10, PatchParam::EXT_TRIG_DEST)
    );

    return UiParamIdx(in_place_type_t<PatchParam>(), table.getP(m_selectedItem));
}

auto EditMenu::MenuStateBank5::onBank5Button()
{
    if (++m_selectedItem == s_nofItems)
    {
        m_selectedItem = 0;
    }
    return Optional<EditMenu::MenuState>(nullopt);
}

Optional<UiParamIdx> EditMenu::MenuStateBank5::getSelectedParam() const
{
    using Table = SparseLUT<SystemParam, uint8_t, s_nofItems>;

    constexpr static const PROGMEM Table table
    (
    SystemParam::NOFENTRIES,
    Table::Entry(0, SystemParam::LOCAL_SWITCH),
    Table::Entry(1, SystemParam::MIDI_SYNC),
    Table::Entry(2, SystemParam::DEVICE_ID),
    Table::Entry(3, SystemParam::RX_EXCLUSIVE),
    Table::Entry(4, SystemParam::PERFORMANCE_CONTROL_CHANNEL),
    Table::Entry(5, SystemParam::REMOTE_KEYBOARD_CHANNEL),
    Table::Entry(6, SystemParam::MIDI_THRU),
    Table::Entry(7, SystemParam::TX_RX_EDIT),
    Table::Entry(8, SystemParam::TX_RX_EDIT_MODE),
    Table::Entry(9, SystemParam::TX_RX_SETTING),
    Table::Entry(10, SystemParam::TX_RX_PROGRAM_CHANGE),
    Table::Entry(11, SystemParam::CONTROL_UP),
    Table::Entry(12, SystemParam::CONTROL_DOWN)
    );

    return UiParamIdx(in_place_type_t<SystemParam>(), table.getP(m_selectedItem));
}

auto EditMenu::MenuStateBank6::onBank6Button()
{
    if (++m_selectedItem == s_nofItems)
    {
        m_selectedItem = 0;
    }
    return Optional<EditMenu::MenuState>(nullopt);
}

Optional<UiParamIdx> EditMenu::MenuStateBank6::getSelectedParam() const
{
    using Table = SparseLUT<SystemParam, uint8_t, s_nofItems>;

    constexpr static const PROGMEM Table table
    (
    SystemParam::NOFENTRIES,
    Table::Entry(0, SystemParam::LCD_CONTRAST),
    Table::Entry(1, SystemParam::MASTER_TUNE),
    Table::Entry(2, SystemParam::POWER_UP_MODE),
    Table::Entry(3, SystemParam::PATTERN_TRIGGER_QUANTIZE),
    Table::Entry(4, SystemParam::MOTION_RESTART)
    );

    return UiParamIdx(in_place_type_t<SystemParam>(), table.getP(m_selectedItem));
}

Optional<UiParamIdx> EditMenu::getSelectedParam()
{
    return visit(
    [this](auto& state) -> Optional<UiParamIdx>
    {
        return state.getSelectedParam();
    },
    m_state
    );
}

void EditMenu::onEditButton()
{
    visit(
    [this](auto& state)
    {
        if (Optional<EditMenu::MenuState> newState = state.onEditButton())
        {
            m_state = *newState;
        }
    },
    m_state
    );

    showState();
}


void EditMenu::onExitButton()
{
    visit(
    [this](auto& state)
    {
        if (Optional<EditMenu::MenuState> newState = state.onExitButton())
        {
            m_state = *newState;
        }
    },
    m_state
    );

    showState();
}

void EditMenu::onBank1Button()
{
    visit(
    [this](auto& state)
    {
        if (Optional<EditMenu::MenuState> newState = state.onBank1Button())
        {
            m_state = *newState;
        }
    },
    m_state
    );

    showSelectedParam();
    showState();
}

void EditMenu::onBank2Button()
{
    visit(
    [this](auto& state)
    {
        if (Optional<EditMenu::MenuState> newState = state.onBank2Button())
        {
            m_state = *newState;
        }
    },
    m_state
    );

    showSelectedParam();
    showState();
}

void EditMenu::onBank3Button()
{
    visit(
    [this](auto& state)
    {
        if (Optional<EditMenu::MenuState> newState = state.onBank3Button())
        {
            m_state = *newState;
        }
    },
    m_state
    );

    showSelectedParam();
    showState();
}

void EditMenu::onBank4Button()
{
    visit(
    [this](auto& state)
    {
        if (Optional<EditMenu::MenuState> newState = state.onBank4Button())
        {
            m_state = *newState;
        }
    },
    m_state
    );

    showSelectedParam();
    showState();
}

void EditMenu::onBank5Button()
{
    visit(
    [this](auto& state)
    {
        if (Optional<EditMenu::MenuState> newState = state.onBank5Button())
        {
            m_state = *newState;
            showSelectedParam();
        }
    },
    m_state
    );

    showState();
}

void EditMenu::onBank6Button()
{
    visit(
    [this](auto& state)
    {
        if (Optional<EditMenu::MenuState> newState = state.onBank6Button())
        {
            m_state = *newState;
        }
    },
    m_state
    );

    showSelectedParam();
    showState();
}

void EditMenu::onBank7Button()
{
    visit(
    [this](auto& state)
    {
        if (Optional<EditMenu::MenuState> newState = state.onBank7Button())
        {
            m_state = *newState;
        }
    },
    m_state
    );

    showState();
}

void EditMenu::onBank8Button()
{
    visit(
    [this](auto& state)
    {
        if (Optional<EditMenu::MenuState> newState = state.onBank8Button())
        {
            m_state = *newState;
        }
    },
    m_state
    );

    showState();
}
