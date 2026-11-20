#include "export_loader.h"

export_loader::export_loader(type_registry& registry)
	: registry{ registry }
{
}

void export_loader::load_test()
{
	load(
		"vec3\n"
		".x:float\n"
		".y:float\n"
		".z:float\n"
		".length():float\n"
		"Enemy\n"
		".position:vec3\n"
		".move(vec3)\n"
	);
}

void export_loader::load(std::string_view text)
{
	while (!text.empty())
	{
		auto end = text.find('\n');
		auto line = text.substr(0, end);
		if (!line.empty() && line.back() == '\r')
		{
			line.remove_suffix(1);
		}
		load_line(line);
		text = end == std::string_view::npos ? std::string_view{} : text.substr(end + 1);
	}
}

void export_loader::load_line(std::string_view line)
{
	if (line.empty())
	{
		return;
	}

	if (line[0] == '.')
	{
		load_member(line.substr(1));
	}
	else
	{
		current_class = &registry.get_class(std::string(line));
	}
}

void export_loader::load_member(std::string_view line)
{
	if (current_class == nullptr)
	{
		throw std::exception("member without class");
	}

	std::string identity, type_name;
	auto colon = line.rfind(':');
	if (colon != std::string_view::npos)
	{
		identity = current_class->name + ":" + std::string(line.substr(0, colon));
		type_name = line.substr(colon + 1);
	}
	else
	{
		identity = line;
	}

	if (identity.find('(') == std::string_view::npos)
	{
		load_property(identity, type_name);
	}
	else
	{
		load_function(identity, type_name);
	}
}

void export_loader::load_property(const std::string& identity, const std::string& type_name)
{
	if (type_name.empty())
	{
		throw std::exception("property without type");
	}
	registry.get_property(*current_class, identity, type_name);
}

void export_loader::load_function(const std::string& identity, const std::string& type_name)
{
	if (identity.back() != ')')
	{
		throw std::exception("missing ')'");
	}

	auto open = identity.find('(');

	std::vector<std::string> params;
	auto list = identity.substr(open + 1, identity.size() - open - 2);
	while (!list.empty())
	{
		auto comma = list.find(',');
		params.emplace_back(list.substr(0, comma));
		list = comma == std::string_view::npos ? std::string_view{} : list.substr(comma + 1);
	}

	registry.get_function(*current_class, identity, params, type_name);
}
