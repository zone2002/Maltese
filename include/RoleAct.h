#ifndef ROLEACT_H
#define ROLEACT_H

#include <QObject>

namespace Act {
Q_NAMESPACE

enum RoleAct {
    Rolling,
    RideScooter,
    RideMaltese,
    Bickering,
    MelodySprint
};
Q_ENUM_NS(RoleAct)
}

#endif // ROLEACT_H
