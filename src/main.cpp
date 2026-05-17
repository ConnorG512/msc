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

  static constexpr auto scale_arg{MSC::create_arg({"s", "scale"}, "Chosen Scale.")};
  static constexpr auto tonic_arg{MSC::create_arg({"t", "tonic"}, "Chosen Tonic.")};

  CLI::App app{"Music scale printer."};
  argv = app.ensure_utf8(argv);

  std::string scale{};
  std::string tonic{};

  app.add_option(scale_arg.args.data(), scale, scale_arg.description.data());
  app.add_option(tonic_arg.args.data(), tonic, tonic_arg.description.data());

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
