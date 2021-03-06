
#include "ClenshawCurtis.H"

#include <stdexcept>
#include <boost/math/constants/constants.hpp>
#include "Polynomial.H"

namespace fsi
{
    namespace quadrature
    {
        using namespace std;
        using namespace boost::math::constants;

        template<typename precision>
        ClenshawCurtis<precision>::ClenshawCurtis( const size_t num_nodes )
            : IQuadrature<precision>( num_nodes )
        {
            if ( this->num_nodes < 2 )
            {
                throw invalid_argument( "Clenshaw-Curtis quadrature requires at least two quadrature nodes." );
            }

            this->compute_nodes();
            this->compute_weights();
        }

        template<typename precision>
        bool ClenshawCurtis<precision>::left_is_node() const
        {
            return LEFT_IS_NODE;
        }

        template<typename precision>
        bool ClenshawCurtis<precision>::right_is_node() const
        {
            return RIGHT_IS_NODE;
        }

        template<typename precision>
        void ClenshawCurtis<precision>::compute_nodes()
        {
            this->nodes = std::vector<precision>( this->num_nodes, precision( 0.0 ) );
            auto roots = Polynomial<precision>::legendre( this->num_nodes ).roots();

            for ( size_t j = 0; j < this->num_nodes; j++ )
            {
                this->nodes[j] = 0.5 * ( 1.0 - std::cos( j * pi<precision>() / (this->num_nodes - 1) ) );
            }
        }
    }
}
