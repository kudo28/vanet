//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package vanet.statistics;
simple StatisticsCollector
{
	parameters:
   		@class(StatisticsCollector);
		string appName = default("StatisticsCollector");

	    @signal[numInfectedSignal](type="long");
		@statistic[numInfected](title="numInfected"; source="numInfectedSignal"; record=vector);

		@signal[numVehiclesSignal](type="long");
		@statistic[numVehicles](title="numVehicles"; source="numVehiclesSignal"; record=vector);
}