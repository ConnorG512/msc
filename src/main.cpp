#include "cli-utils.hpp"
#include "fnv1a.hpp"
#include "search.hpp"

#include "CLI11.hpp"

#include <array>
#include <cstdlib>
#include <exception>
#include <print>
#include <string>
#include <string_view>

int main(int argc, char **argv)
{
  if (argc == 1)
  {
    std::println(stdout, "No arguments provided, see --help/-h for more information.");
    return EXIT_SUCCESS;
  }

  CLI::App app{"Music scale printer."};
  argv = app.ensure_utf8(argv);

  std::string scale{};
  std::string tonic{};

  static constexpr auto cli_args = std::to_array<MSC::CmdArg<16,32>>({
    MSC::CmdArg<>{{"s", "scale"}, "Chosen Scale."},
    MSC::CmdArg<>{{"t", "tonic"}, "Chosen Tonic."}
  });

  app.add_option(cli_args.at(0).get_arg<std::string>(), scale, cli_args.at(0).get_description<std::string>());
  app.add_option(cli_args.at(1).get_arg<std::string>(), tonic, cli_args.at(1).get_description<std::string>());

  try
  {
    app.parse(argc, argv);
    MSC::search(MSC::generate_hash(scale.data()), MSC::generate_hash(tonic.data()));
  }
  catch (const CLI::ParseError &e)
  {
    return app.exit(e);
  }
  catch (std::exception &e)
  {
    std::println(stderr, "Exception caught! Error: {}", e.what());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
