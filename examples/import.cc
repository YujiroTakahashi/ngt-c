#include <stdlib.h>
#include <iostream>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

#include <croco/ngt/Index.h>

int main(int argc, char **argv)
{
    croco::Index index;
    index.create(300);

    if (3 > argc) {
        std::cout << "./import_ngt [user name] [user passwd]\n";
        exit(1);
    }

    try {
        sql::Driver *driver = get_driver_instance();
        sql::Connection *con = driver->connect("tcp://localhost:3306", argv[1], argv[2]);

        con->setSchema("ngt");

        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM `index` WHERE id = ?");
        pstmt->setInt(1, 1);
        pstmt->execute();

        sql::ResultSet *res = pstmt->getResultSet();

        while (res->next()) {
            {
                std::istream *blb = res->getBlob("objects");
                
                std::string input(
                    (std::istreambuf_iterator<char>(*blb)), 
                    std::istreambuf_iterator<char>()
                );
                index.setObjectString(input);
            }
            {
                std::istream *blb = res->getBlob("distances");
                std::string input(
                    (std::istreambuf_iterator<char>(*blb)), 
                    std::istreambuf_iterator<char>()
                );
                index.setDistanceString(input);
            }
            {
                std::istream *blb = res->getBlob("leafNodes");
                std::string input(
                    (std::istreambuf_iterator<char>(*blb)), 
                    std::istreambuf_iterator<char>()
                );
                index.setLeafNodeString(input);
            }
            {
                std::istream *blb = res->getBlob("internalNodes");
                std::string input(
                    (std::istreambuf_iterator<char>(*blb)), 
                    std::istreambuf_iterator<char>()
                );
                index.setInternalNodeString(input);
            }
        }
        index.importIndex();
    } catch (sql::SQLException e) {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }

    std::vector<float> query = {
        0.021593, -0.013728, -0.025222, -0.10652, -0.0072144, -0.023198, 0.025298, 0.013533, 0.046633, -0.037416, 
        0.0015004, 0.035886, -0.019384, -0.03127, 0.03192, -0.01173, -0.062024, -0.030848, -0.039921, 0.034673, 
        0.01716, -0.04269, -0.02971, -0.0082751, 0.02036, -0.064246, 0.037503, 0.019448, 0.020177, -0.053324, 
        -0.0039145, -0.015519, -0.065727, -0.070551, -0.046416, -0.034357, -0.041681, -0.068942, 0.071483, -0.047291, 
        0.026799, 0.03936, 0.026494, -0.041393, -0.043053, -0.017916, 0.023624, 0.027435, 0.025567, 0.015203, 
        -0.043387, 0.029254, -0.012582, 0.062093, 0.013701, -0.014624, -0.01548, 0.029065, -0.039762, 0.025926, 
        0.0052232, 0.02543, 0.0032234, 0.038302, -0.029415, -0.016186, 0.043645, 0.038234, 0.084588, -0.062317, 
        0.034106, 0.037469, -0.059511, 0.051891, -0.061112, -0.00018574, 0.0073689, 0.031974, -0.044364, 0.046784, 
        -0.023643, 0.065515, 0.025522, 0.15232, 0.0046407, 0.010817, 0.028013, 0.044813, -0.027235, -0.040301, 
        0.0029193, -0.029488, -0.039612, 0.045216, -0.0028404, -0.012544, -0.026839, 0.0022989, 0.084118, -0.059528, 
        0.020251, -0.037436, 0.027523, 0.062394, -0.050231, -0.081399, -0.036514, 0.052345, -0.020397, -0.052121, 
        -0.02965, -0.060396, -0.0089224, 0.052535, -0.055856, 0.018505, 0.050422, 0.060044, -0.067418, 0.050471, 
        -0.04957, 0.031262, -0.04317, 0.060269, -0.074957, -0.077933, 0.1003, -0.030309, -0.065373, 0.095403, 
        -0.020841, -0.049816, -0.026832, 0.05389, 0.006716, -0.057391, 0.065065, -0.030653, -0.013675, -0.077705, 
        -0.054888, 0.048337, -0.44027, -0.033704, 0.027524, -0.033761, 0.057897, 0.066164, -0.058839, 0.048877, 
        -0.06652, -0.028238, 0.055454, -0.041595, -0.060659, 0.054943, -0.063566, -0.07995, 0.074463, -0.089579, 
        0.033741, 0.013757, 0.0054379, -0.021389, 0.021708, -0.090225, -0.088741, 0.066036, -0.087915, 0.051464, 
        0.074936, 0.05886, 0.083432, 0.049463, 0.043253, 0.035571, -0.031334, 0.065403, 0.08047, 0.072292, 
        0.019278, 0.023993, 0.018175, -0.019689, 0.056303, 0.013778, 0.060594, 0.034988, -0.017293, 0.01872, 
        -0.014209, 0.046576, 0.0062162, -0.031477, -0.055581, 0.0096534, -0.0082444, 0.053578, -0.038052, 0.047378, 
        -0.030833, 0.070358, 0.044447, 0.051635, 0.042405, -0.025837, -0.061336, 0.023398, 0.11149, -0.0093883, 
        0.057212, -0.026332, 0.046692, 0.039131, 0.034849, -0.038315, 0.073418, 0.030626, 0.034411, 0.039285, 
        -0.026074, 0.047913, -0.021243, 0.042853, -0.052451, 0.025301, 0.027506, -0.043104, -0.064948, -0.03121, 
        0.019469, -0.049536, -0.026087, -0.041789, 0.003629, 0.021902, -0.012119, -0.0088071, -0.0087212, -0.0070248, 
        0.042598, 0.090651, -0.06351, -0.050883, 0.1259, 0.043926, -0.02241, -0.025324, -0.039169, -0.035672, 
        -0.033712, -0.058824, 0.08323, 0.072274, -0.029799, -0.060807, -0.017491, -0.059349, 0.046371, 0.022585, 
        0.042935, 0.0096756, -0.04805, -0.087372, -0.049599, 0.053633, 0.062058, 0.010607, 0.0057323, -0.047695, 
        -0.052099, -0.015673, -0.062431, 0.023462, -0.016697, -0.057025, 0.057897, -0.091861, 0.019719, -0.08604, 
        -0.012648, 0.066788, -0.035954, 0.054719, 0.091156, 0.019246, 0.08825, -0.040683, 0.019947, -0.016102, 
        -0.056239, 0.102, -0.07049, 0.011525, 0.0085731, 0.03665, -0.038483, 0.044468, 0.04081, -0.044913
    };
    std::vector<std::pair<int, float>> res = index.search(query, 5);
    for (const auto& row : res) {
        std::cout << row.first << ":" << row.second << "\n";
    }

    return 0;
}
