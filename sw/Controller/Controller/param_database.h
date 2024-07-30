/*
Copyright (C) 2024 Andreas Lagler

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

#ifndef PARAM_DATABASE_H
#define PARAM_DATABASE_H

#include "ui_param_def.h"

class ParamDatabase
{
    public:
    
    ParamDatabase();
    
    constexpr UiParamValue& getParamValue(const PatchParam param)
    {
        return m_params[getParamIndex(param, isUpperPartSelected())];
    }

    constexpr UiParamValue& getParamValue(const PartParam param)
    {
        return m_params[getParamIndex(param, isUpperPartSelected())];
    }
    
    constexpr UiParamValue& getParamValue(const PerformanceParam param)
    {
        return m_params[getParamIndex(param)];
    }

    constexpr UiParamValue& getParamValue(const SystemParam param)
    {
        return m_systemParams[static_cast<uint8_t>(param)];
    }

    constexpr UiParamValue& getParamValue(const UiParamIdx& param)
    {
        return visit(
        [this](const auto& param) -> UiParamValue&
        {
            return getParamValue(param);
        },
        param);
    }


    constexpr const UiParamValue& getParamValue(const PatchParam param) const
    {
        return m_params[getParamIndex(param, isUpperPartSelected())];
    }

    constexpr const UiParamValue& getParamValue(const PartParam param) const
    {
        return m_params[getParamIndex(param, isUpperPartSelected())];
    }

    constexpr const UiParamValue& getParamValue(const PerformanceParam param) const
    {
        return m_params[getParamIndex(param)];
    }

    constexpr const UiParamValue& getParamValue(const SystemParam param) const
    {
        return m_systemParams[static_cast<uint8_t>(param)];
    }

    constexpr const UiParamValue& getParamValue(const UiParamIdx& param) const
    {
        return visit(
        [this](const auto& param) -> const UiParamValue&
        {
            return getParamValue(param);
        },
        param);
    }

    
    constexpr bool isUpperPartSelected() const
    {
        switch (get<PartSelect>(getParamValue(PerformanceParam::PART_SELECT)))
        {
            case PartSelect::UPPER:
            case PartSelect::LOWER_UPPER:
            return true;
            
            default:
            return false;
        }
    }

    private:
    
    constexpr uint8_t getParamIndex(const PatchParam param, const bool upperPart) const
    {
        return static_cast<uint8_t>(param) + (upperPart) ? (static_cast<uint8_t>(PatchParam::NOFENTRIES) + static_cast<uint8_t>(PartParam::NOFENTRIES)) : 0;
    }
    
    constexpr uint8_t getParamIndex(const PartParam param, const bool upperPart) const
    {
        return static_cast<uint8_t>(param) + static_cast<uint8_t>(PatchParam::NOFENTRIES) + (upperPart) ? (static_cast<uint8_t>(PatchParam::NOFENTRIES) + static_cast<uint8_t>(PartParam::NOFENTRIES)) : 0;
    }
    
    constexpr uint8_t getParamIndex(const PerformanceParam param) const
    {
        return static_cast<uint8_t>(param) + 2 * static_cast<uint8_t>(PatchParam::NOFENTRIES) + 2 * static_cast<uint8_t>(PartParam::NOFENTRIES);
    }
        
    static constexpr uint8_t nofParams = 2 * static_cast<uint8_t>(PatchParam::NOFENTRIES) + 2 * static_cast<uint8_t>(PartParam::NOFENTRIES) + static_cast<uint8_t>(PerformanceParam::NOFENTRIES);
    Array<UiParamValue, nofParams> m_params;
    Array<UiParamValue, static_cast<uint8_t>(SystemParam::NOFENTRIES)> m_systemParams;

};

#endif