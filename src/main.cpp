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
  
  // Cmd Args:
  CLI::App app{"Music scale printer."};
  argv = app.ensure_utf8(argv);

  std::string scale{};
  std::string tonic{};
  bool list_triggered{};

  static constexpr auto cli_args = std::to_array<MSC::CmdArg<16, 32>>(
      {MSC::CmdArg<>{{"s", "scale"}, "Chosen Scale."}, MSC::CmdArg<>{{"t", "tonic"}, "Chosen Tonic."}});
  enum class Args {
    Scale, 
    Tonic,
  };
  app.add_option(cli_args.at(std::to_underlying(Args::Scale)).get_arg<std::string>(), scale, cli_args.at(std::to_underlying(Args::Scale)).get_description<std::string>());
  app.add_option(cli_args.at(std::to_underlying(Args::Tonic)).get_arg<std::string>(), tonic, cli_args.at(std::to_underlying(Args::Tonic)).get_description<std::string>());
  app.add_flag("-l,--list", list_triggered, "Show scale list");
  
  // Execute:
  try
  {
    app.parse(argc, argv);
    if(list_triggered)
    {
      MSC::list();
      return EXIT_SUCCESS;
    }

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
