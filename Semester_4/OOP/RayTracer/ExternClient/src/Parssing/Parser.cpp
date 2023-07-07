/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** parser
*/

#include "Parser.hpp"

RT::Parser::Parser()
{
}

RT::Parser::Parser(std::string filepath)
{
    init(filepath);
}

RT::Parser::~Parser()
{
}

void RT::Parser::init(std::string filepath)
{
    try {
        _cfg.readString(filepath);
    }
    catch(const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        throw;
    }
    catch(const libconfig::ParseException& pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        throw;
    }
}

RT::Parsing::Camera RT::Parser::getInfoCam()
{
    if (_cfg.exists("camera")) {
        libconfig::Setting& tmp = _cfg.lookup("camera");
        RT::Parsing::Camera camera;
        camera.create(tmp);
        _camera = camera;
    }
    return (_camera);
}

RT::Parsing::Light RT::Parser::getInfoLight()
{
    if (_cfg.exists("light")) {
        libconfig::Setting& tmp = _cfg.lookup("light");
        RT::Parsing::Light light;
        light.create(tmp);
        _light = light;
    }
    return (_light);
}

std::vector<std::shared_ptr<RT::Parsing::IObjParser>> RT::Parser::getInfo()
{
    if (_cfg.exists("primitive")) {
        libconfig::Setting& ma_variable = _cfg.lookup("primitive");
        getObj(ma_variable, "default");
    }
    return (_obj);
}

void RT::Parser::checkObj(libconfig::Setting& cfg, std::shared_ptr<RT::Parsing::IObjParser> &obj, std::string name)
{
    if (cfg.getType() == libconfig::Setting::TypeString) {
        readFile(cfg.c_str());
    } else {
        if (cfg.getType() == libconfig::Setting::TypeList) {
            RT::Parsing::Factory factory;
            for (int i = 0; i < cfg.getLength(); i++) {
                std::shared_ptr<RT::Parsing::IObjParser> _tmp = factory.createFactory(name);
                _tmp->create(cfg[i]);
                _tmp->setGroup(cfg.getName());
                if (i + 1 != cfg.getLength())
                    _obj.push_back(_tmp);
                obj = _tmp;
            }
        }
    }
}

void RT::Parser::getObj(libconfig::Setting& cfg, std::string name)
{
    RT::Parsing::Factory factory;
    for (int i = 0; i < cfg.getLength(); i++) {
        libconfig::Setting& res = cfg.lookup(cfg[i].getName());

        //Factory
        std::shared_ptr<RT::Parsing::IObjParser> obj_tmp = factory.createFactory(cfg[i].getName());
        if (obj_tmp != nullptr) {
            checkObj(res, obj_tmp, cfg[i].getName());
            _obj.push_back(obj_tmp);
            _obj_map[name].push_back(obj_tmp);

        //Obj unknown and parse with file
        } else if (cfg[i].getType() == libconfig::Setting::TypeString) {
            std::string str = cfg[i];
            auto it = _filepath.find(str);
            if (str.find(".obj") != std::string::npos)
                fillObj(str, it, cfg[i].getName());
            else
                readFile(res);
        //Obj unknown
        } else {
            std::cerr << "Bad arguments" << std::endl;
        }
    }
}

void RT::Parser::readFile(std::string filepath)
{
    libconfig::Config cfg;
    try {
        cfg.readFile(filepath.c_str());
    }
    catch(const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
    }
    catch(const libconfig::ParseException& pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
    }
    if (cfg.exists("primitive")) {
        libconfig::Setting& ma_variable = cfg.lookup("primitive");
        getObj(ma_variable, filepath);
    }
}

void RT::Parser::getClassObj(size_t begin, RT::ParserObj obj, std::string name)
{
    size_t tab_m = 0;
    std::vector<double> tmp;
    std::vector<double> default_color = {255, 255, 255};
    std::map<long long, std::string> stock_materials;
    std::vector<std::vector<std::vector<double>>> vertices = obj.getVerticesOfFaces(begin);
    RT::Parsing::Factory factory;

    for (size_t x = 0; x < vertices.size(); x++) {

        for (size_t y = 0; y < vertices[x].size(); y++) {

            for (size_t z = 0; z < vertices[x][y].size(); z++) {
                tmp.push_back(vertices[x][y][z]);
            }
        }

        if (obj.getMaterials().size() > 0) {
            stock_materials = obj.getMaterials()[begin];

            //Change the value of the tab_m and tab_s
            if (stock_materials.find(x) != stock_materials.end())
                tab_m = x;
        }

        if (tmp.size() % 3 == 0 && tab_m < obj.getMaterials().size()) {
            std::shared_ptr<RT::Parsing::IObjParser> obj_tmp = factory.createFactory("triangle");
            obj_tmp->set(tmp, "lambertian", default_color, (double)0.5);
            obj_tmp->setGroup(name);
            _obj.push_back(obj_tmp);
            if (_obj_map.find(name) == _obj_map.end())
                _obj_map.insert(std::make_pair(name, _obj));
            else
                _obj_map[name].push_back(obj_tmp);


        } else if (tab_m < obj.getMaterials().size()) {
            std::shared_ptr<RT::Parsing::IObjParser> obj_tmp = factory.createFactory("rectangle");
            obj_tmp->set(tmp, stock_materials[tab_m], default_color, (double)1);
            obj_tmp->setGroup(name);
            _obj.push_back(obj_tmp);
            if (_obj_map.find(name) == _obj_map.end())
                _obj_map.insert(std::make_pair(name, _obj));
            else
                _obj_map[name].push_back(obj_tmp);
        }
        tmp.clear();
    }
}

void RT::Parser::fillObj(std::string str, std::map<std::string, RT::ParserObj>::iterator it, std::string name)
{
    if (it != _filepath.end()) {
        _obj.insert(_obj.end(), _obj_map[name].begin(), _obj_map[name].end());
    } else {
        ParserObj obj;
        obj.create(str);
        _filepath.insert(std::make_pair(str, obj));
        for (size_t begin = 0; begin < obj.getNbFaces(); begin++) {
            getClassObj(begin, obj, name);
        }
    }
}
