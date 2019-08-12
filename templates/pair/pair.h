#ifndef PAIR_H
#define PAIR_H
///////////////////////////////////////////////////////////////////////
// pair.h - demonstrate class templates                              //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004         //
///////////////////////////////////////////////////////////////////////
//
//   class pair packs two objects into a container for transportation.
//   Can help a function return more than one object.
//
namespace demo
{
  template <class L, class R> class pair
  {
  public:
    pair(const pair<L,R>& p) : lft(p.lft), rgt(p.rgt) {}
    pair(const L& larg, const R&  rarg) : lft(larg), rgt(rarg) {}
    L  left() const { return lft; }
    R right() const { return rgt; }
    void  left(const L& larg) { lft = larg; }
    void right(const R& rarg) { rgt = rarg; }
  private:
    L lft;
    R rgt;
  };
}
#endif
