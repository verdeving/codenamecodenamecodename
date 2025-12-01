#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "Lens.hpp"
#include "IR.hpp"
#include "../Iris/Ircode.hpp"

namespace Iris::Lens
{
    [[nodiscard]] auto lens(const std::string& , const Cornea::CompilationUnit& , const
    std::string content) noexcept -> std::optional<IR>
    {
        IR ir;
        std::string opcode;
        enum class [[nodiscard]] Context : std::uint8_t
        {
            General,
            Main,

        };
        using enum Context;
        Context context = General;
        for(const char character : content)
            switch(context)
            {
                case General:
                    opcode.append(1uz, character);
                    if(opcode.size() == 3uz)
                    {
                        if(opcode == Ircode::start_main)
                        {
                            context = Main;
                            ir.emplace_back(Entry{});
                        }
                        opcode.clear();
                    }
                break;
                case Main:
                    opcode.append(1uz, character);
                    if(opcode.size() == 3uz)
                    {
                        if(opcode == Ircode::end_main)
                        {
                            context = General;
                            ir.emplace_back(Exit{});
                        }
                        opcode.clear();
                    }
            }
        return ir;
    }
}

#endif