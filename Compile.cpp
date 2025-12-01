#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "Compile.hpp"
#include "File.hpp"
#include "Error.hpp"
#include "Project.hpp"
#include "../Iris/Iris.hpp"
#include "../Lens/Lens.hpp"
#include "../Optic/Optic.hpp"
#include "../Cornea/Cornea.hpp"

namespace Iris
{
    auto compile(std::string name) noexcept -> void
    {
        const Project project{std::move(name)};
        if(project.iris.empty())
            Error::log(project.src, "no source (.iris) files");
        else
        {
            const std::optional<std::vector<Cornea::CompilationUnit>> units = Cornea::cornea(project.
            cornea, File::read(project.cornea));
            if(units.has_value())
                for(const Cornea::CompilationUnit& unit : *units)
                {
                    Main main;
                    for(const std::string& file : project.iris)
                        if(not iris(file, File::read(file), unit, main))
                            goto next_compilation_unit;
                    if(unit.type == Cornea::Type::App and not main.loaded)
                        Error::log<11uz>(Language::iris, unit, "the project's " + Error::token +
                        "type" + Error::normal + " is an " + Error::token + "app" + Error::normal +
                        ", and no " + Error::token + "main" + Error::normal + " was found");
                    else
                    {
                        for(const std::string& file : project.iris)
                        {
                            std::optional<Lens::IR> ir = Lens::lens(file, unit, File::read(File::
                            iris_abstract_tree(file)));
                            if(ir.has_value())
                                Optic::optic(File::lens_intermediate_representation(file), unit, *
                                ir);
                            else
                                goto next_compilation_unit;
                        }
                        // Nerve::nerve();
                    }
                    next_compilation_unit:;
                }
        }
    }
}

#endif