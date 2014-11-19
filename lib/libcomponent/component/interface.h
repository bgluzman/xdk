#ifndef __COMPONENT_INTERFACE_H__
#define __COMPONENT_INTERFACE_H__

#include "types.h"

namespace Component
{


  /**
   * The component type.
   */
  typedef enum {
    NIC_COMPONENT = 0,    /**< The NIC component type. */
    STACK_COMPONENT = 1,  /**< The Stack component type. */
    MEM_COMPONENT = 2,    /**< The Memory component type. */
  } component_t;

  enum { MAX_INSTANCE = 10 };

  /** 
   * Base class. All interfaces must inherit from this class.
   */

  class Interface_base
  {
    component_t _comp_type;
    state_t     _comp_state[MAX_INSTANCE];

  public:
    /** 
     * To initialize the component interface.
     *
     * @param arg A struct pointer for configuration arguments.
     * @return The return status.
     */
    virtual status_t init(arg_t arg) = 0;

    /** 
     * To bind another interface pointed by itf.
     *
     * @param itf An interface pointer.
     * @return The return status.
     */
    virtual status_t bind(interface_t itf) = 0;

    /** 
     * To specify the cpu allocation for this interface.
     *
     * @param mask The CPU mask to indicate which CPUs are used.
     * @return The return status.
     */
    virtual status_t cpu_allocation(cpu_mask_t mask) = 0;
 
    /** 
     * To start the interface.
     */
    virtual void run() = 0;

    /** 
     * To obtain the component type.
     *
     * @return The type of this component.
     */
    component_t get_comp_type() {
      return _comp_type;
    }

    /** 
     * To set the component type.
     *
     * @param t The component type to be set.
     */
    void set_comp_type(component_t t) {
      _comp_type = t;
    }

    /** 
     * To obtain the state of component.
     *
     * @return The runtime state of current component.
     */
    state_t get_comp_state(unsigned idx) {
      return _comp_state[idx];
    }
    
    /** 
     * To set the component state.
     *
     * @param s The component state to be set.
     */
    void set_comp_state(state_t s, unsigned idx) {
      _comp_state[idx] = s;
    }
  };

}
#endif