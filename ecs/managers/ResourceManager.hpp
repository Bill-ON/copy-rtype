#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <string>
#include <unordered_map>
#include <stdexcept>

template <typename Resource>
class ResourceManager
{
public:
    ResourceManager(std::string const &, std::string const &);

    Resource &get_resource(std::string const &);

private:
    std::string get_filepath(std::string const &);
    void add_resource(std::string const &);
    bool resource_exists(std::string const &);
    void remove_resource(std::string const &);

    std::string _folder;
    std::string _fail;
    std::unordered_map<std::string, Resource> _resources;
};

template <typename Resource>
inline ResourceManager<Resource>::ResourceManager(std::string const &folder, std::string const &fail)
    : _folder("assets/" + folder + "/"),
      _fail(_folder + fail)
{
}

template <typename Resource>
inline Resource &ResourceManager<Resource>::get_resource(std::string const &name)
{
    if (!resource_exists(name))
    {
        add_resource(name);
    }
    return _resources.at(name);
}

template <typename Resource>
inline std::string ResourceManager<Resource>::get_filepath(std::string const &name)
{
    return _folder + name;
}

template <typename Resource>
inline void ResourceManager<Resource>::add_resource(std::string const &name)
{
    Resource r;

    if (!r.loadFromFile(get_filepath(name)))
    {
        // Resource fail;
        // fail.loadFromFile(get_filepath("fail"));
        // _resources.insert(std::make_pair(name, fail));
        //
        throw std::runtime_error("Could not load resource: " + get_filepath(name));
    }
    _resources.insert(std::make_pair(name, r));
}

template <typename Resource>
inline bool ResourceManager<Resource>::resource_exists(std::string const &name)
{
    return _resources.find(name) != _resources.end();
}

template <typename Resource>
inline void ResourceManager<Resource>::remove_resource(std::string const &name)
{
    _resources.erase(name);
}

#endif /* RESOURCE_MANAGER_HPP */
