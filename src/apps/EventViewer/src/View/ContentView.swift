import SwiftUI

struct ContentView: View {
    @State private var selection: String? = "Main"

    let version = Bundle.main.object(forInfoDictionaryKey: "CFBundleVersion") as! String

    var body: some View {
        VStack {
            NavigationView {
                VStack(alignment: .leading, spacing: 0) {
                    List {
                        NavigationLink(destination: MainView(),
                                       tag: "Main",
                                       selection: $selection) {
                            Label("Main", systemImage: "magnifyingglass")
                        }
                        .padding(10)

                        NavigationLink(destination: FrontmostApplicationView(),
                                       tag: "FrontmostApplication",
                                       selection: $selection) {
                            Label("FrontmostApplication", systemImage: "checkmark.circle")
                        }
                        .padding(10)

                        NavigationLink(destination: VariablesView(),
                                       tag: "Variables",
                                       selection: $selection) {
                            Label("Variables", systemImage: "cube")
                        }
                        .padding(10)

                        NavigationLink(destination: DevicesView(),
                                       tag: "Devices",
                                       selection: $selection) {
                            Label("Devices", systemImage: "keyboard")
                        }
                        .padding(10)

                        NavigationLink(destination: PreferencesView(),
                                       tag: "Preferences",
                                       selection: $selection) {
                            Label("Preferences", systemImage: "gearshape")
                        }
                        .padding(10)
                    }
                    .listStyle(SidebarListStyle())
                    .frame(width: 250)

                    Spacer()
                }
            }
        }.frame(minWidth: 1100, minHeight: 650)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}