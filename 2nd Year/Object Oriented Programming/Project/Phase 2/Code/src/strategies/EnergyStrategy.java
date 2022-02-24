package strategies;

import entities.humaninstances.InstanceDistributor;
import entities.humaninstances.InstanceProducer;

import java.util.ArrayList;

/**
 * Interface used for the Strategy design pattern.
 */
public interface EnergyStrategy {

    /**
     *
     */
    public void initializeStrategy(ArrayList<InstanceProducer> producers,
                                   ArrayList<InstanceProducer> indexed,
                                   InstanceDistributor distributor, long monthlyUpdate);
}
