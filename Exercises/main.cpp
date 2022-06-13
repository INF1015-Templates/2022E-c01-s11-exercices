
#include <cstddef>
#include <cstdint>

#include <cassert>
#include <fstream>
#include <filesystem>
#include <stdexcept>

#include <QException>
#include <QApplication>
#include <QMessageBox>

#include <view/CompanyWindow.hpp>
#include <utils/List.hpp>
#include <utils/MyClass.hpp>

using namespace std;
using namespace utils;


int runQtExample(int argc, char* argv[]) {
	struct Application : public QApplication {
		using QApplication::QApplication;

		bool notify(QObject* receiver, QEvent* event) override {
			try {
				return QApplication::notify(receiver, event);
			} catch (exception& e) {
				QMessageBox::critical(
					nullptr,
					tr("Unhandled exception caught."),
					tr(e.what())
				);
				QApplication::exit(EXIT_FAILURE);
				return false;
			}
		}
	};

	Application a(argc, argv);
	view::CompanyWindow w;
	w.createEmployee("Employee", "Mohamed Doyon", 42);
	w.createEmployee("Employee", "Kevin Barrette", 69);
	w.createEmployee("Secretary", "Alyson Nolin", 420);
	w.createEmployee("Secretary", "Robert Thomas", 1337);
	w.createEmployee("Manager", "David Ducharme", 0xDEAD, 10);
	w.createEmployee("Manager", "Claude Hernandez", 0xBEEF, 15);

	w.show();
	return a.exec();
}

List<int> parseFile(const string& filename, bool printListEachStep = true) {
	// Ici, le but de l'exercice est de faire un programme qui construit une liste liée à partir de valeurs entières et de commandes dans un fichier.
	// Les commandes sont "popf" et "popb" qui enlève le premier et le dernier élément de la liste, respectivement. Les valeurs et commandes sont séparées par des espaces.
	// Par exemple, le fichier contenant "42 1337 69" fera la liste [42 1337 69]
	// "42 1337 69 popf" donne [1337 69]
	// "42 1337 69 popb" donne [42 1337]
	// "42 1337 popb 69" donne [42 69]

	static auto hasDataLeft = [] (istream& file) {
		return not(file.eof() or ws(file).eof());
	};

	List<int> values;

	try {
		ifstream file(filename);
		file.exceptions(ios::failbit);

		if (printListEachStep)
			cout << values << "\n";
		while (hasDataLeft(file)) {
			try {
				string x;
				file >> x;
				if (x == "popf")
					values.pop_front();
				else if (x == "popb")
					values.pop_back();
				else {
					try {
						values.push_back(stoi(x, nullptr, 0));
					} catch (invalid_argument& e) {
						cout << "Unrecognized value or command: " << x << "\n";
					}
				}
				// On affiche la liste à chaque opération si demandé.
				if (printListEachStep)
					cout << values << "\n";
			} catch (EmptyListError& e) {
				cout << e.what() << "\n";
			}
		}
	} catch (ios::failure& e) {
		cout << e.what() << "\n" << e.code() << "\n";
	}

	return values;
}

void runRaiiExample() {
	using namespace utils;

	{
		try {
			cout << "---A---" << "\n";
			unique_ptr<MyClass> foo = make_unique<MyClass>();
			throw 42;
			cout << "---B---" << "\n";
		} catch (...) {
			cout << "---C---" << "\n";
		}
		cout << "---D---" << "\n";
	}
	cout << "- - - - - - - - - - - - - - - - - - -" << "\n";
	{
		struct Spam {
			Spam() : m(make_unique<MyClass>()) {
				printDefCtor("Spam");
				{ throw 42; }
			}
			~Spam() {
				printDtor("Spam");
			}

			unique_ptr<MyClass> m;
		};
		try {
			cout << "---A---" << "\n";
			Spam spam;
			cout << "---B---" << "\n";
		} catch (...) {
			cout << "---C---" << "\n";
		}
		cout << "---D---" << "\n";
	}
}

double fn1_assert(double x, double y) {
	assert(x != y);
	return (x+y)/(x-y);
}

pair<double, bool> fn1_pair(double x, double y) {
	return {(x+y)/(x-y), x != y};
}

optional<double> fn1_opt(double x, double y) {
	if (x == y)
		return {};
	return (x+y)/(x-y);
}

double fn1_except(double x, double y) {
	if (x == y)
		// Erreur dont on peut récupérer.
		throw logic_error("Div by 0");
	return (x+y)/(x-y);
}

void runSimpleExceptExample() {

	auto&& [res, ok] = fn1_pair(5, 5);
	if (ok)
		cout << res << "\n";
	else
		cout << "Numerical error" << "\n";

	optional<double> res2 = fn1_opt(5, 5);
	if (res2)
		cout << *res2 << "\n";
	else
		cout << "Numerical error" << "\n";

	try {
		double res3 = fn1_except(5, 5);
		cout << res3 << "\n";
	} catch (logic_error& e) {
		cout << "Error: " << e.what() << "\n";
	}

	cout << "Ok I'm done" << "\n";
}

double fn1(double x, double y) {
	if (x == y)
		throw logic_error("Division by zero (x == y)");
	if (isinf(x) or isinf(y))
		throw system_error(error_code{}, "One argument is infinity");
	if (isnan(x) or isnan(y))
		throw "One argument is NaN"s;
	return (x + y) / (x - y);
}

void fn2() {
	static string msg = "Hello, world!";
	
	cout << msg << "\n";
	msg += " Bonjour";
}


int main(int argc, char* argv[]) {
	//while (true) {
	//	cout << "Enter x, y: ";
	//	double x, y;
	//	cin >> x >> y;
	//	try {
	//		double result = fn1(x, y);
	//		cout << "(x + y) / (x - y) = " << result << "\n";
	//		break;
	//	} catch (logic_error& e) {
	//		cout << "Caught std::logic_error : " << e.what() << "\n";
	//	} catch (system_error& e) {
	//		cout << "Caught std::system_error : " << e.code() << ", " << e.what() << "\n";
	//	} catch (exception& e) {
	//		cout << "Unspecified exception : " << e.what() << "\n";
	//	} catch (...) {
	//		cout << "Unknown exception caught." << "\n";
	//	}

	//	auto&& [ok, result] = fn1(x, y);
	//	if (ok) {
	//		cout << "(x + y) / (x - y) = " << result << "\n";
	//		break;
	//	}
	//	else 
	//		cout << "Invalid result or arguments." << "\n";
	//}

	//return runQtExample(argc, argv);

	//try {
	//	filesystem::remove("values.txt");
	//	ofstream("values.txt") << "1 42 69 popf 9000 popb popb popf popf henlo 42 0xBEEF 0xRAWR";
	//	List<int> values = parseFile("values.txt", true);
	//	cout << "Values: " << values << "\n";
	//} catch (system_error& e) {
	//	cout << e.what() << e.code();
	//} catch (exception& e) {
	//	cout << e.what();
	//	throw e;
	//} catch (...) {
	//	cout << "Unrecognized exception caught" << "\n";
	//}

	//runRaiiExample();
	
	//runSimpleExceptExample();
}
