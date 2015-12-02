

template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size) : currentSize{ 0 }
      { theLists.resize( prime_below(size) ); }

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
    makeEmpty();
    currentSize = 0;
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k)
{
    auto & whichList = theLists[ myhash( k ) ];
    return std::find_if(whichList.begin(), whichList.end(), [&k](std::pair<K, V> const & elem) 
      {return elem.first == k;}) != std::end( whichList );
   
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K,V> &kv) const  
{
    auto & whichList = theLists[ myhash( kv.first ) ];
    return find( begin( whichList ), end( whichList ), kv ) != end( whichList); 
   
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K,V> & kv)
{
    auto & whichList = theLists[ myhash( kv.first ) ];
    if( std::find_if(whichList.begin(), whichList.end(), [&kv](std::pair<K, V> const & elem) 
      {return elem.first == kv.first;}) != std::end( whichList ))
      return false;
    
    whichList.push_back( kv );

        // Rehash; see Section 5.5
    if( ++currentSize > theLists.size( ) )
        rehash( );

    return true;
}

template <typename K, typename V>
bool HashTable<K, V>::insert (std::pair<K,V> && kv)
{
    auto & whichList = theLists[ myhash( kv.first) ];      
    if( std::find_if(whichList.begin(), whichList.end(), [&kv](std::pair<K, V> const & elem) 
      {return elem.first == kv.first;}) != std::end( whichList ))
      return false;
    whichList.push_back( std::move( kv ) );

        // Rehash; see Section 5.5
    if( ++currentSize > theLists.size( ) )
        rehash( );

    return true;
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k)
{
    auto & whichList = theLists[ myhash( k ) ];
    auto itr = std::find_if(whichList.begin(), whichList.end(), [&k](std::pair<K, V> const & elem) 
               {return elem.first == k;});

    if( itr == end( whichList ))
        return false;

    whichList.erase( itr );
    --currentSize;
    return true;
}

template <typename K, typename V>
void HashTable<K, V>::clear()
{
    makeEmpty();
    currentSize = 0;
}

template <typename K, typename V>
void HashTable<K, V>::dump()
{
  int count = 0;
    for(int i=0; i<theLists.size();i++)
    {
        auto & eachList = theLists[i];
        count = 0;
        std::cout << "v[" << i << "]: ";
        for(auto & elem : eachList)
        {
          if(count > 0)
              std::cout << ":";
          std::cout << elem.first << " " <<  elem.second;
          count++;
        }
      //  if(count > 0)
      //    std::cout << "." ;
        std::cout << std::endl;
    }
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename)
{
    std::string key;
    std::string value; 
    std::string line; 
    std::ifstream input_file(filename);
    
    if(input_file.is_open())
    {
        while ( getline (input_file,line)) 
        {
            std::stringstream ss(line);
            ss >> key;
            ss >> value;
            insert(make_pair(key, value));  
            currentSize++;
        }   
        return true;     
    } 
    else
    {
        std::cout << "Unable to open input file." << std::endl; 
        return false;
    }
}

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename)
{
    std::ofstream out_file;
    out_file.open(filename);

    if (out_file.is_open())
    {
       for(auto & eachList : theLists)
       {
          for(auto & elem : eachList)
          {
              out_file << elem.first << " " << elem.second << std::endl;
          }
       }
       out_file.close();
       return true;
    }
      else
      {
        std::cout << "Unable to open output file." << std::endl;
        return false;
      }
}

//private methods
template <typename K, typename V>
void HashTable<K, V>::makeEmpty( )
{
    for( auto & thisList : theLists )
        thisList.clear( );
    theLists.resize(0) ; 
}

template <typename K, typename V>
void HashTable<K, V>::rehash( )
{
    std::vector<std::list<std::pair<K,V>>> oldLists = theLists;

        // Create new double-sized, empty table
    theLists.resize( prime_below( 2 * theLists.size( ) ) );
    for( auto & thisList : theLists )
        thisList.clear( );

        // Copy table over
    currentSize = 0;
    for( auto & thisList : oldLists )
        for( auto & x : thisList )
            insert( std::move( x ) );
}

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const
{
    static std::hash<K> hf;
    return hf( k ) % theLists.size( );
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

