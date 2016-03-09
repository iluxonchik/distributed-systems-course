package ttt;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class TTTServer {
    public static void main(String[] args) {
        int registryPort = 9001;
        try {
            TTTService ttt = new TTT();
            // create a "private" remote object registry (i.e. one that is used by this server
            // only and not shared by multiple servers)
            Registry reg = LocateRegistry.createRegistry(registryPort);
            reg.rebind("ttt", ttt);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }
}
