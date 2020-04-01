#ifndef MAPOBJECT_H
#define MAPOBJECT_H

class MapObject
{

public:

    enum Type { Floor, Robot, Wall, None };

    enum Direction { North, South, East, West };

    enum Material { MagneticNorth, MagneticSouth, Metal, Neutral };


    MapObject();


    Type type() const;

    Direction direction() const;

    Material plateMaterial(const Direction direction) const;

    bool isRigid() const;

    bool isObjective() const;


    void type(const Type type);

    void direction(const Direction direction);

    void plateMaterial(const Direction direction, const Material material);

    void isRigid(const bool isRigid);

    void isObjective(const bool isObjective);

    bool operator !=(const MapObject &other);

    bool operator ==(const MapObject &other);

private:

    Type _type;

    Direction _direction;

    Material _plateNorth;

    Material _plateSouth;

    Material _plateEast;

    Material _plateWest;

    bool _isRigid;

    bool _isObjective;

};

#endif // MAPOBJECT_H
