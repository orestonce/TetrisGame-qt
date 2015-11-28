#ifndef RESTONCE_OBSERVER_H
#define RESTONCE_OBSERVER_H

namespace restonce {

class Observer
{
protected:
    Observer() = default;
    virtual ~Observer() = default;
public:
    virtual void onSubjectChanged() = 0;
};

} // namespace restonce

#endif // RESTONCE_OBSERVER_H
